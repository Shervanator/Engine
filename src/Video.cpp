#include "Video.h"
#include "Logger.h"

Video::Video(const std::string file)
{
  av_register_all();

  if (avformat_open_input(&m_formatContext, file.c_str(), NULL, NULL) != 0) {
    log_err("Error Loading Video %s", file.c_str());
    return;
  }

  if (avformat_find_stream_info(m_formatContext, NULL) < 0) {
    log_err("Error Finding Stream Info");
    return;
  }

  m_videoStream = -1;
  for (int i = 0; i < m_formatContext->nb_streams; i++) {
    if (m_formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
      m_videoStream = i;
      break;
    }
  }

  if (m_videoStream == -1) {
    log_err("Error Finding Video Stream");
    return;
  }

  m_codecContext = m_formatContext->streams[m_videoStream]->codec;
  m_frameRate = m_formatContext->streams[m_videoStream]->r_frame_rate.num / 1000;

  m_codec = avcodec_find_decoder(m_codecContext->codec_id);
  if (m_codec == NULL) {
    log_err("Unsupported Codec");
    return;
  }

  if (avcodec_open2(m_codecContext, m_codec, NULL) < 0) {
    log_err("Error opening Codec");
    return;
  }

  m_frame = av_frame_alloc();
  m_frameRGB = av_frame_alloc();
  if (m_frameRGB == NULL) {
    log_err("Error allocating frame");
    return;
  }

  int numBytes = avpicture_get_size(PIX_FMT_RGB24, m_codecContext->width,
                                m_codecContext->height);
  m_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

  avpicture_fill((AVPicture *) m_frameRGB, m_buffer, PIX_FMT_RGB24,
                 m_codecContext->width, m_codecContext->height);

  m_SwsContext = sws_getContext(m_codecContext->width,
                           m_codecContext->height, m_codecContext->pix_fmt,
                           m_codecContext->width, m_codecContext->height,
                           PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);

  if (m_SwsContext == NULL) {
    log_err("Cannot initialize the sws context");
    return;
  }
}

Video::~Video(void)
{
   av_free(m_buffer);
   av_free(m_frameRGB);
   av_free(m_frame);
   avcodec_close(m_codecContext);
   avformat_close_input(&m_formatContext);
}

int Video::getWidth(void)
{
  return m_codecContext->width;
}

int Video::getHeight(void)
{
  return m_codecContext->height;
}

uint8_t* Video::nextFrame(void)
{
  int retVal;
  while ((retVal = av_read_frame(m_formatContext, &m_packet)) >= 0) {
    if (m_packet.stream_index == m_videoStream) {
      avcodec_decode_video2(m_codecContext, m_frame, &m_frameFinished, &m_packet);

      if (m_frameFinished) {
        sws_scale(m_SwsContext,
                  (const uint8_t * const *) m_frame->data,
                  m_frame->linesize, 0, m_codecContext->height,
                  m_frameRGB->data,
                  m_frameRGB->linesize);

        m_frameFinished = 0;
        break;
      }
    }

    av_free_packet(&m_packet);
  }

  if (retVal >= 0) {
    return m_frameRGB->data[0];
  } else {
    return nullptr;
  }
}

int Video::getFrameRate(void)
{
  return m_frameRate;
}

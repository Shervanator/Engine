#include "Video.h"

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

Video::Video(const std::string file)
{
  av_register_all();

  AVFormatContext *pFormatCtx = NULL;
  if (avformat_open_input(&pFormatCtx, file, NULL, NULL) != 0)
    exit(1);

  if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    exit(1);

  int videoStream = -1;
  for (i = 0; i < pFormatCtx->nb_streams; i++) {
    if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
      videoStream = i;
      break;
    }
  }

  if (videoStream == -1)
    exit(1);

  AVCodecContext *pCodecCtx = pFormatCtx->streams[videoStream]->codec;
  int frameRate = pFormatCtx->streams[videoStream]->r_frame_rate.num / 1000;

  AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
  if (pCodec == NULL) {
    fprintf(stderr, "Unsupported codec!\n");
    exit(1);
  }

  if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    exit(1);

  AVFrame *pFrame = av_frame_alloc();
  AVFrame *pFrameRGB = av_frame_alloc();
  if (pFrameRGB == NULL)
    exit(1);

  int numBytes = avpicture_get_size(PIX_FMT_RGBA, pCodecCtx->width, pCodecCtx->height);
  uint8_t *buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

  avpicture_fill((AVPicture *) pFrameRGB, buffer, PIX_FMT_RGBA,
                 pCodecCtx->width, pCodecCtx->height);

  struct SwsContext *pSwsCtx = sws_getContext(pCodecCtx->width,
                           pCodecCtx->height, pCodecCtx->pix_fmt,
                           pCodecCtx->width, pCodecCtx->height,
                           PIX_FMT_RGBA, SWS_FAST_BILINEAR, NULL, NULL, NULL);

  if (pSwsCtx == NULL) {
    fprintf(stderr, "Cannot initialize the sws context\n");
    exit(1);
  }

  int frameFinished;

  AVPacket packet;

  while (av_read_frame(pFormatCtx, &packet) >= 0) {
          log_info("INITIAL FRAME");

    if (packet.stream_index == videoStream) {
      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

      if (frameFinished) {
        sws_scale(pSwsCtx,
                  (const uint8_t * const *) pFrame->data,
                  pFrame->linesize, 0, pCodecCtx->height,
                  pFrameRGB->data,
                  pFrameRGB->linesize);

        frameFinished = 0;
        break;
      }


    }

    av_free_packet(&packet);
  }
}

Video::~Video(void)
{
}

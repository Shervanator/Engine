#ifndef VIDEO_H
#define VIDEO_H

#include <string>
extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}

class Video
{
public:
  Video(const std::string file);
  ~Video(void);

  uint8_t *nextFrame(void);
  int getWidth(void);
  int getHeight(void);
  int getFrameRate(void);

private:
  AVFormatContext *m_formatContext = NULL;
  AVCodecContext *m_codecContext;
  AVCodec *m_codec;
  AVFrame *m_frame;
  AVFrame *m_frameRGB;
  int m_videoStream;
  int m_frameRate;
  struct SwsContext *m_SwsContext;
  uint8_t *m_buffer;
  AVPacket m_packet;
  int m_frameFinished;
};

#endif

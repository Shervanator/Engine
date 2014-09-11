#include "CustomIOStream.h"

CustomIOStream::CustomIOStream(void)
{
}

CustomIOStream::~CustomIOStream(void)
{
}

size_t CustomIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount)
{
  return 0;
}

size_t CustomIOStream::Write(const void* pvBuffer, size_t pSize, size_t pCount)
{
  return 0;
}

aiReturn CustomIOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
  return AI_SUCCESS;
}

size_t CustomIOStream::Tell(void) const
{
  return 0;
}

size_t CustomIOStream::FileSize(void) const
{
  return 0;
}

void CustomIOStream::Flush(void)
{
}


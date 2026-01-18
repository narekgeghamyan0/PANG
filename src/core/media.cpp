#include "media.h"

Media::Media(std::string path, MediaType type)
     : filePath_(std::move(path)), type_(type)
{
}

MediaType Media::getType() const
{
    return type_;
}

const std::string& Media::getPath() const
{
    return filePath_;
}

bool Media::isSaved() const
{
    return id_.has_value();
}

bool Media::isPhoto() const
{
    return type_ == MediaType::Photo;
}

bool Media::isVideo() const
{
    return type_ == MediaType::Video;
}

bool Media::isAudio() const
{
    return type_ == MediaType::Audio;
}

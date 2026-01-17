#include "media.h"

Media::Media(std::string& path, MediaType type)
     : filePath_(std::move(path)), type_(type)
{
}

MediaType Media::getType() const
{
    return type_;
}

std::string Media::getPath() const
{
    return file_path;
}

bool Media::isSaved() const
{
    return id_.has_value();
}

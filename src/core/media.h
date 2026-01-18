#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <optional>

enum MediaType {
    Photo,
    Video,
    Audio
};

class Media
{
public:
    Media(std::string path, MediaType type);
public:
    MediaType getType() const;
    const std::string& getPath() const;
    bool isSaved() const;
    bool isPhoto() const;
    bool isVideo() const;
    bool isAudio() const;
private:
    MediaType type_;
    std::optional<uint32_t> id_;
    std::string filePath_;
};

#endif // MEDIA_H
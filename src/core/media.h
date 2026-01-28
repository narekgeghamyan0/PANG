#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <optional>
#include <cstdint>
#include <chrono>

enum MediaType {
    Photo,
    Video,
    Audio
};

/// Type aliases
using TimePoint = std::chrono::system_clock::time_point;
using IdType = uint32_t;

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
    std::optional<IdType> id_;
    std::string filePath_;
};

#endif // MEDIA_H
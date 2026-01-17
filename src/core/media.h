#ifndef _MEDIA_H_
#define _MEDIA_H_

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
    Media(std::string& path, MediaType type);
public:
    MediaType getType() const;
    std::string getPath() const;
    bool isSaved() const;
private:
    MediaType type_;
    std::optional<uint32_t> id_;
    std::string file_path;
};

#endif // _MEDIA_H_
#ifndef LOGGER_H
#define LOGGER_H

// logging macros
#if defined(ABYSS_DEBUG)
#define ABYSS_LOG(level, color, message, ...) \
        std::printf("%s", color); \
        fprintf(stderr, "[%s] ", level); \
        fprintf(stderr, message, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
        std::printf("\x1B[0m");

// Yellow color
#define ABYSS_WARNING(message, ...) ABYSS_LOG("warning", "\x1B[33m", message, ##__VA_ARGS__)

// Red color
#define ABYSS_ERROR(message, ...) ABYSS_LOG("error", "\x1B[31m", message, ##__VA_ARGS__)

// Green color
#define ABYSS_INFO(message, ...) ABYSS_LOG("info", "\x1B[32m", message, ##__VA_ARGS__)
#else
#define ABYSS_INFO
#define ABYSS_ERROR
#define ABYSS_WARNING
#endif

#endif // !LOGGER_H

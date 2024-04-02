#include "Audio.h"

Audio ::Audio()
{

}

Audio ::~Audio()
{
    Mix_FreeChunk(wavChunk);
    Mix_CloseAudio();
}

void Audio::load(const char* filename)
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // Xử lý lỗi khi không thể khởi tạo
        // Thông báo lỗi hoặc thực hiện các hành động phù hợp
    }

    // Tải âm thanh từ tệp WAV vào Mix_Chunk
    wavChunk = Mix_LoadWAV(filename);
    if(wavChunk == nullptr) {
        // Xử lý lỗi khi không thể tải âm thanh
        // Thông báo lỗi hoặc thực hiện các hành động phù hợp
    }
}

void Audio ::play()
{
    if(Mix_PlayChannel(-1, wavChunk, -1) == -1) {
        // Xử lý lỗi khi không thể phát âm thanh
        // Thông báo lỗi hoặc thực hiện các hành động phù hợp
    }
}

void Audio::stop() {
    // Dừng phát âm thanh từ Mix_Chunk
    Mix_HaltChannel(-1);
}

void Audio::pause() {
    // Tạm dừng phát âm thanh từ Mix_Chunk
    Mix_Pause(-1);
}

void Audio::resume() {
    // Tiếp tục phát âm thanh từ Mix_Chunk
    Mix_Resume(-1);
}










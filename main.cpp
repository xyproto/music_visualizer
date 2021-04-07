#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include <thread>
using std::string;
#include <chrono>
using ClockT = std::chrono::steady_clock;
#include <fstream>
using std::ifstream;
#include <stdexcept>
using std::runtime_error;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <ffts/ffts.h>
#include <filesystem>
#include <pulse/pulseaudio.h>

#include "MFileWatcher.h"
#include "filesystem.h"

#include "Renderer.h"
#include "ShaderConfig.h"
#include "ShaderPrograms.h"
#include "Window.h"

#include "AudioProcess.h"
#ifdef WINDOWS
#include "ProceduralAudioStream.h"
#include "WindowsAudioStream.h"
using AudioStreamT = WindowsAudioStream;
// using AudioStreamT = ProceduralAudioStream;
#else
#include "LinuxAudioStream.h"
using AudioStreamT = LinuxAudioStream;
#endif
using AudioProcessT = AudioProcess<ClockT, AudioStreamT>;

// TODO rename to shader player (like vmware player) ?
// TODO adding builtin uniforms should be as easy as adding an entry to a list

#if defined(WINDOWS) && defined(DEBUG)
int WinMain()
{
#else
int main(int argc, char* argv[])
{
#endif

    filesys::path shader_folder(SHADERDIR);

    filesys::path config_folder(RESOURCEDIR);

    // TODO should this be here or in ShaderConfig?
    filesys::path shader_config_path = config_folder / "shader.json";

    FileWatcher watcher(shader_folder);

    ShaderConfig* shader_config = nullptr;
    ShaderPrograms* shader_programs = nullptr;
    Renderer* renderer = nullptr;
    Window* window = nullptr;
    // TODO extract to get_valid_config(&, &, &, &)
    while (!(shader_config && shader_programs && window)) {
        try {
            shader_config = new ShaderConfig(shader_folder, shader_config_path);
            window = new Window(
                shader_config->mInitWinSize.width, shader_config->mInitWinSize.height);
            renderer = new Renderer(*shader_config, *window);
            shader_programs
                = new ShaderPrograms(*shader_config, *renderer, *window, shader_folder);
            renderer->set_programs(shader_programs);
        } catch (runtime_error& msg) {
            cout << msg.what() << endl;

            // something failed so reset state
            delete shader_config;
            delete shader_programs;
            delete window;
            delete renderer;
            shader_config = nullptr;
            shader_programs = nullptr;
            window = nullptr;
            renderer = nullptr;

            while (!watcher.files_changed()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }
    cout << "Successfully compiled shaders." << endl;

    // AudioStreamT audio_stream(); // Most Vexing Parse
    AudioStreamT audio_stream;
    AudioProcessT audio_process { audio_stream, shader_config->mAudio_ops };
    std::thread audio_thread
        = std::thread(&AudioProcess<ClockT, AudioStreamT>::start, &audio_process);
    if (shader_config->mAudio_enabled)
        audio_process.start_audio_system();

    auto update_shader = [&]() {
        cout << "Updating shaders." << endl;
        try {
            ShaderConfig new_shader_config(shader_folder, shader_config_path);
            Renderer new_renderer(new_shader_config, *window);
            ShaderPrograms new_shader_programs(
                new_shader_config, new_renderer, *window, shader_folder);
            *shader_config = new_shader_config;
            *shader_programs = std::move(new_shader_programs);
            *renderer = std::move(new_renderer);
            renderer->set_programs(shader_programs);
        } catch (runtime_error& msg) {
            cout << msg.what() << endl;
            cout << "Failed to update shaders." << endl << endl;
            return;
        }
        if (shader_config->mAudio_enabled) {
            audio_process.start_audio_system();
            audio_process.set_audio_options(shader_config->mAudio_ops);
        } else {
            audio_process.pause_audio_system();
        }
        cout << "Successfully updated shaders." << endl << endl;
    };

    while (window->is_alive()) {
        if (watcher.files_changed())
            update_shader();
        auto now = ClockT::now();
        renderer->update(audio_process.get_audio_data());
        renderer->render();
        window->swap_buffers();
        window->poll_events();
        std::this_thread::sleep_for(std::chrono::microseconds(16666) - (ClockT::now() - now));
    }

    audio_process.exit_audio_system();
    audio_thread.join();

    return 0;
}

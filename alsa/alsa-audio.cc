
// Alsa API docs: in the http://www.alsa-project.org/alsa-doc/alsa-lib/ page.

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include "alsa/asoundlib.h"

//SND_PCM_ACCESS_RW_INTERLEAVED

using namespace std;

static void set_hw_parameters(snd_pcm_t * pcm)
{
    int alsa_errcode;

    snd_pcm_hw_params_t * hwparams;

    alsa_errcode = snd_pcm_hw_params_malloc(&hwparams);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params_any(pcm, hwparams);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params_set_rate(pcm, hwparams, 48000, 0);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params_set_access(pcm, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params_set_format(pcm, hwparams, SND_PCM_FORMAT_S16);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params_set_channels(pcm, hwparams, 2);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_hw_params(pcm, hwparams);
    assert(alsa_errcode == 0);

    snd_pcm_hw_params_free(hwparams);
}

static void set_sw_parameters(snd_pcm_t * pcm)
{
    int alsa_errcode;

    snd_pcm_sw_params_t * swparams;

    alsa_errcode = snd_pcm_sw_params_malloc(&swparams);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_sw_params_current(pcm, swparams);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_pcm_sw_params(pcm, swparams);
    assert(alsa_errcode == 0);

    snd_pcm_sw_params_free(swparams);
}

int main()
{
    int alsa_errcode; // used to check return values of ALSA calls.

    snd_pcm_t * pcm;

    const char * alsa_devicename = "default";

    alsa_errcode = snd_pcm_open(&pcm, alsa_devicename, SND_PCM_STREAM_PLAYBACK, 0);
    assert(alsa_errcode == 0);

    cout << "Opened PCM device: \"" << snd_pcm_name(pcm) << "\"" << endl;

    cout << "Configuring HW parameters ..." << endl;

    set_hw_parameters(pcm);

    cout << "Configuring SW parameters ..." << endl;

    set_sw_parameters(pcm);

    cout << "Pushing samples ..." << endl;

    const unsigned max_buffer_frames = 1000;

    int16_t buffer[max_buffer_frames][2];
    unsigned num_buffer_frames = 0;

    for (unsigned frameNr = 0; frameNr < 48000 * 2; ++frameNr)
    {
        double t = frameNr / 48000.0;

        buffer[num_buffer_frames][0] = round(sin(2 * M_PI * 660.0 * t) * 10000); // left
        buffer[num_buffer_frames][1] = round(sin(2 * M_PI * 440.0 * t) * 10000); // right

        ++num_buffer_frames;

        if (num_buffer_frames == max_buffer_frames)
        {
            snd_pcm_sframes_t frames = snd_pcm_writei(pcm, buffer, num_buffer_frames);
            assert(frames == num_buffer_frames);
            num_buffer_frames = 0;
        }
    }

    if (num_buffer_frames != 0)
    {
        snd_pcm_sframes_t frames = snd_pcm_writei(pcm, buffer, num_buffer_frames);
        assert(frames == num_buffer_frames);
        num_buffer_frames = 0;
    }

    cout << "Closing PCM device: \"" << snd_pcm_name(pcm) << "\"" << endl;
    alsa_errcode = snd_pcm_close(pcm);
    assert(alsa_errcode == 0);

    alsa_errcode = snd_config_update_free_global();
    assert(alsa_errcode == 0);

    cout << "Free resources ..." << endl;

    return EXIT_SUCCESS;
}

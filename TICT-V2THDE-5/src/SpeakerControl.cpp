#include "SpeakerControl.hpp"

speakerControl::speakerControl(/*hwlib::target::pin_out* speakerOutput*/) : task(5, "SpeakerControl"),
                                                                            //lsp(speakerOutput),
                                                                            shootSoundFlag(this, "shootSoundFlag"),
                                                                            startSoundFlag(this, "startSoundFlag"),
                                                                            endSoundFlag(this, "endSoundFlag")
{
}

void speakerControl::play(const note &n)
{
    if (n.frequency == 0)
    {
        hwlib::wait_us(n.duration);
    }
    else
    {
        auto half_period = 1'000'000 / (2 * n.frequency);
        auto end = hwlib::now_us() + n.duration;
        do
        {
            lsp.write(1);
            lsp.flush();
            hwlib::wait_us(half_period);
            lsp.write(0);
            lsp.flush();
            hwlib::wait_us(half_period);
        } while (end > hwlib::now_us());
    }
}

void speakerControl::setShootSoundFlag(void)
{
    shootSoundFlag.set();
}

void speakerControl::setStartSoundFlag(void)
{
    startSoundFlag.set();
}

void speakerControl::setEndSoundFlag(void)
{
    endSoundFlag.set();
}

void speakerControl::playGameOverSound(void)
{
    play(note{note::G5, note::d8});
    play(note{note::F5, note::dF});
    play(note{note::B4, note::dF});
    play(note{note::A4, note::dF});
}

void speakerControl::playStartSound(void)
{
    play(note{note::B4, note::d8});
    play(note{note::B4, note::d8});
    play(note{note::B5, note::dQ});
    play(note{note::E5, note::dQ});
    play(note{note::A4, note::d8});
    play(note{note::A4, note::d8});
    play(note{note::A4, note::d8});
    play(note{note::A5, note::dH});
}

void speakerControl::playShootSound(void)
{
    play(note{note::A5, note::d8});
    play(note{note::B5, note::d8});
    play(note{note::C5, note::d8});
    play(note{note::D5, note::d8});
}

void speakerControl::main(void)
{
    for (;;)
    {
        auto evt = wait(shootSoundFlag + startSoundFlag + endSoundFlag);
        if (evt == shootSoundFlag)
        {
            playShootSound();
        }
        else if (evt == startSoundFlag)
        {
            playStartSound();
        }
        else if (evt == endSoundFlag)
        {
            playGameOverSound();
        }
    }
}
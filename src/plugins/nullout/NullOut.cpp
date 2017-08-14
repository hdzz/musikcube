//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007-2016 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#include "NullOut.h"

#include <core/sdk/constants.h>

using namespace musik::core::sdk;

#ifdef WIN32
    #include <Windows.h>
    #define usleep(x) Sleep(x / 1000);
#else
    #include <unistd.h>
#endif

NullOut::NullOut() {
    this->volume = 1.0f;
    this->state = StateStopped;
}

NullOut::~NullOut() {
}

void NullOut::Destroy() {
    delete this;
}

void NullOut::Pause() {
    this->state = StatePaused;
}

void NullOut::Resume() {
    this->state = StatePlaying;
}

void NullOut::SetVolume(double volume) {
    this->volume = volume;
}

double NullOut::GetVolume() {
    return this->volume;
}

void NullOut::Stop() {
    this->state = StateStopped;
}

void NullOut::Drain() {

}

IDeviceList* NullOut::GetDeviceList() {
    return nullptr;
}

bool NullOut::SetDefaultDevice(const char* deviceId) {
    return false;
}

IDevice* NullOut::GetDefaultDevice() {
    return nullptr;
}

int NullOut::Play(IBuffer *buffer, IBufferProvider *provider) {
    if (this->state == StatePaused) {
        return OutputInvalidState;
    }

    /* order of operations matters, otherwise overflow. */
    int micros = ((buffer->Samples() * 1000) / buffer->SampleRate() * 1000) / buffer->Channels();
    usleep(micros);
    provider->OnBufferProcessed(buffer);
    return OutputBufferWritten;
}

double NullOut::Latency() {
    return 0.0;
}
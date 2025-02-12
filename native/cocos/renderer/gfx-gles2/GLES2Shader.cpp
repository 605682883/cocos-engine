/****************************************************************************
 Copyright (c) 2019-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "GLES2Std.h"

#include "GLES2Commands.h"
#include "GLES2Device.h"
#include "GLES2Shader.h"

namespace cc {
namespace gfx {

GLES2Shader::GLES2Shader() {
    _typedID = generateObjectID<decltype(this)>();
}

GLES2Shader::~GLES2Shader() {
    destroy();
}

void GLES2Shader::doInit(const ShaderInfo & /*info*/) {
    _gpuShader = ccnew GLES2GPUShader;
    _gpuShader->name = _name;
    _gpuShader->blocks = _blocks;
    _gpuShader->samplerTextures = _samplerTextures;
    _gpuShader->subpassInputs = _subpassInputs;

    for (const auto &stage : _stages) {
        _gpuShader->gpuStages.push_back({stage.stage, stage.source});
    }

    cmdFuncGLES2CreateShader(GLES2Device::getInstance(), _gpuShader);

    // Clear shader source after they're uploaded to GPU
    for (auto &stage : _gpuShader->gpuStages) {
        stage.source.clear();
        stage.source.shrink_to_fit();
    }

    for (auto &stage : _stages) {
        stage.source.clear();
        stage.source.shrink_to_fit();
    }
}

void GLES2Shader::doDestroy() {
    if (_gpuShader) {
        cmdFuncGLES2DestroyShader(GLES2Device::getInstance(), _gpuShader);
        delete _gpuShader;
        _gpuShader = nullptr;
    }
}

} // namespace gfx
} // namespace cc

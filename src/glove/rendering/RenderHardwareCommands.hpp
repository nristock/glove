#pragma once

#include <vector>

#include "glove/CommonTypes.hpp"
#include "glove/GloveApi.hpp"
#include "glove/rendering/RenderHardwareInterface.hpp"
#include "glove/rendering/RenderTarget.hpp"

namespace glove {

struct GLOVE_API_EXPORT RenderHardwareCommand {
  public:
    virtual ~RenderHardwareCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const = 0;

    virtual void Visualize(std::ostream& ostream) const { ostream << "Unknown command"; }
};

// Begin of generated section, do not modify manually
// [GENERATE:COMMANDS]
struct SetViewportCommand : public RenderHardwareCommand {
  public:
    SetViewportCommand(int32 x, int32 y, int32 width, int32 height) : x(x), y(y), width(width), height(height) {}
    virtual ~SetViewportCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.SetViewport(x, y, width, height); }

    virtual void Visualize(std::ostream& ostream) const {
        ostream << "SetViewport {";
        ostream << "x: " << x;
        ostream << " y: " << y;
        ostream << " width: " << width;
        ostream << " height: " << height;
        ostream << "}";
    }

    const int32 x;
    const int32 y;
    const int32 width;
    const int32 height;
};

struct SetScissorRectCommand : public RenderHardwareCommand {
  public:
    SetScissorRectCommand(int32 x, int32 y, int32 width, int32 height) : x(x), y(y), width(width), height(height) {}
    virtual ~SetScissorRectCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.SetScissorRect(x, y, width, height); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "SetScissorRect"; }

    const int32 x;
    const int32 y;
    const int32 width;
    const int32 height;
};

struct SetRenderTargetsCommand : public RenderHardwareCommand {
  public:
    SetRenderTargetsCommand(const std::vector<RenderTarget>& colorTargets, const RenderTarget& depthStencilTarget)
        : colorTargets(colorTargets), depthStencilTarget(depthStencilTarget) {}
    virtual ~SetRenderTargetsCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.SetRenderTargets(colorTargets, depthStencilTarget); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "SetRenderTargets"; }

    const std::vector<RenderTarget> colorTargets;
    const RenderTarget depthStencilTarget;
};

struct EnableVertexBindingCommand : public RenderHardwareCommand {
  public:
    EnableVertexBindingCommand(const std::shared_ptr<VertexBinding>& vertexBinding) : vertexBinding(vertexBinding) {}
    virtual ~EnableVertexBindingCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.EnableVertexBinding(vertexBinding); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "EnableVertexBinding"; }

    const std::shared_ptr<VertexBinding> vertexBinding;
};

struct EnableShaderProgramCommand : public RenderHardwareCommand {
  public:
    EnableShaderProgramCommand(const std::shared_ptr<ShaderProgram>& shaderProgram) : shaderProgram(shaderProgram) {}
    virtual ~EnableShaderProgramCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.EnableShaderProgram(shaderProgram); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "EnableShaderProgram"; }

    const std::shared_ptr<ShaderProgram> shaderProgram;
};

struct BindTexture2DCommand : public RenderHardwareCommand {
  public:
    BindTexture2DCommand(const std::shared_ptr<Texture2D>& texture, const uint32& textureSlot)
        : texture(texture), textureSlot(textureSlot) {}
    virtual ~BindTexture2DCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.BindTexture2D(texture, textureSlot); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "BindTexture2D"; }

    const std::shared_ptr<Texture2D> texture;
    const uint32 textureSlot;
};

struct SetUniformParameterCommand : public RenderHardwareCommand {
  public:
    SetUniformParameterCommand(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter,
                               const glm::mat4& value)
        : uniformParameter(uniformParameter), value(value) {}
    virtual ~SetUniformParameterCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.SetUniformParameter(uniformParameter, value); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "SetUniformParameter"; }

    const std::shared_ptr<UniformParameter::UniformIndex> uniformParameter;
    const glm::mat4 value;
};

struct SetIntUniformParameterCommand : public RenderHardwareCommand {
  public:
    SetIntUniformParameterCommand(const std::shared_ptr<UniformParameter::UniformIndex>& uniformParameter,
                                  const uint32& value)
        : uniformParameter(uniformParameter), value(value) {}
    virtual ~SetIntUniformParameterCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.SetIntUniformParameter(uniformParameter, value); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "SetIntUniformParameter"; }

    const std::shared_ptr<UniformParameter::UniformIndex> uniformParameter;
    const uint32 value;
};

struct DrawIndexedPrimitiveCommand : public RenderHardwareCommand {
  public:
    DrawIndexedPrimitiveCommand(const std::shared_ptr<IndexBuffer>& indexBuffer, const uint32& firstIndex,
                                const uint32& lastIndex)
        : indexBuffer(indexBuffer), firstIndex(firstIndex), lastIndex(lastIndex) {}
    virtual ~DrawIndexedPrimitiveCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const {
        rhi.DrawIndexedPrimitive(indexBuffer, firstIndex, lastIndex);
    }

    virtual void Visualize(std::ostream& ostream) const { ostream << "DrawIndexedPrimitive"; }

    const std::shared_ptr<IndexBuffer> indexBuffer;
    const uint32 firstIndex;
    const uint32 lastIndex;
};

struct ClearFramebufferCommand : public RenderHardwareCommand {
  public:
    ClearFramebufferCommand(const bool& clearColor, const bool& clearDepth, const bool& clearStencil)
        : clearColor(clearColor), clearDepth(clearDepth), clearStencil(clearStencil) {}
    virtual ~ClearFramebufferCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const {
        rhi.ClearFramebuffer(clearColor, clearDepth, clearStencil);
    }

    virtual void Visualize(std::ostream& ostream) const { ostream << "ClearFramebuffer"; }

    const bool clearColor;
    const bool clearDepth;
    const bool clearStencil;
};

struct BeginFrameCommand : public RenderHardwareCommand {
  public:
    BeginFrameCommand(const std::shared_ptr<ViewportClient>& viewportClient) : viewportClient(viewportClient) {}
    virtual ~BeginFrameCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.BeginFrame(viewportClient); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "BeginFrame"; }

    const std::shared_ptr<ViewportClient> viewportClient;
};

struct EndFrameCommand : public RenderHardwareCommand {
  public:
    EndFrameCommand(const std::shared_ptr<ViewportClient>& viewportClient, const RenderTarget& presentSource)
        : viewportClient(viewportClient), presentSource(presentSource) {}
    virtual ~EndFrameCommand() = default;

    virtual void Execute(RenderHardwareInterface& rhi) const { rhi.EndFrame(viewportClient, presentSource); }

    virtual void Visualize(std::ostream& ostream) const { ostream << "EndFrame"; }

    const std::shared_ptr<ViewportClient> viewportClient;
    const RenderTarget presentSource;
};

// [\GENERATE:COMMANDS]
}

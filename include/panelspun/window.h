// SPDX-License-Identifier: Apache-2.0 OR MIT
#pragma once

#include <memory>
#include <string>

#include "panelspun/panel.h"
#include "panelspun/split_tree.h"
#include "panelspun/vulkan_region.h"

namespace panelspun {

struct WindowConfig {
    std::string title = "panelspun";
    int width = 1280;
    int height = 800;
    Theme theme;
    // Enables the Khronos validation layer; creation fails if the layer is not installed.
    bool vulkanValidation = false;
};

class Window {
public:
    // Returns nullptr and fills error when SDL, Vulkan or ThorVG cannot start.
    static std::unique_ptr<Window> create(const WindowConfig& config, SplitTree layout, std::string* error);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // The panel id must already be a leaf of the layout.
    bool setPanel(const std::string& id, std::unique_ptr<Panel> panel);

    SplitTree& layout();
    const VulkanContext& vulkan() const;

    // Pumps events and presents until the window closes or frameLimit frames are presented.
    int run(int frameLimit = 0);
    void requestRedraw();
    void requestClose();

    // Copies the next presented frame to a BMP file.
    void captureNextFrame(std::string path);
    bool lastCaptureSucceeded() const;
    int validationErrors() const;

    struct Impl;

private:
    explicit Window(std::unique_ptr<Impl> impl);
    std::unique_ptr<Impl> impl_;
};

}

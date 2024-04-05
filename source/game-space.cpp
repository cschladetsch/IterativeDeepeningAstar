#include <utility>
#include "SDL.h"

struct Grid {
    using Dimenions = std::pair<size_t, size_t>;

    Grid(size_t width, size_t height)
        : _grid({ width, height }) {
    }

    void ChangeWindow(SDL_Window * window) {
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        _pixels = {width, height};
    }

    void Render(SDL_Renderer& renderer) const {
        SDL_SetRenderDrawColor(&renderer, 64, 64, 64, 255);

        int cellWidth = _pixels.first / _grid.first;
        int cellHeight = _pixels.second / _grid.second;

        for (size_t x = 0; x <= _grid.first; ++x) {
            SDL_RenderDrawLine(&renderer, x * cellWidth, 0, x * cellWidth, _pixels.second);
        }

        for (size_t y = 0; y <= _grid.second; ++y) {
            SDL_RenderDrawLine(&renderer, 0, y * cellHeight, _pixels.first, y * cellHeight);
        }
    }

private:
    Dimenions _pixels, _grid;
};



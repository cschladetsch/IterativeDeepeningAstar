#include <utility>
#include "SDL.h"
#include <stdexcept>

class SDLManager {
public:
    SDLManager() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        }
    }

    ~SDLManager() {
        SDL_Quit();
    }

    SDL_Window* CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags) {
        SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (!window) {
            throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
        }
        return window;
    }

    SDL_Renderer* CreateRenderer(SDL_Window* window, Uint32 flags) {
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, flags);
        if (!renderer) {
            throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
        }
        return renderer;
    }
};

struct Grid {
    using Dimensions = std::pair<size_t, size_t>;

    Grid(size_t width, size_t height)
        : _grid({ width, height }) {
    }

    void ChangeWindow(SDL_Window* window) {
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        _pixels = { static_cast<size_t>(width), static_cast<size_t>(height) };
    }

    void Render(SDL_Renderer& renderer) const {
        DrawGridLines(renderer);
    }

private:
    void DrawGridLines(SDL_Renderer& renderer) const {
        // Set the drawing color to dark grey
        SDL_SetRenderDrawColor(&renderer, 64, 64, 64, 255);

        // Calculate the width and height of each cell in pixels
        int cellWidth = static_cast<int>(_pixels.first / _grid.first);
        int cellHeight = static_cast<int>(_pixels.second / _grid.second);

        // Draw vertical lines
        for (size_t x = 0; x <= _grid.first; ++x) {
            SDL_RenderDrawLine(&renderer, static_cast<int>(x * cellWidth), 0, static_cast<int>(x * cellWidth), static_cast<int>(_pixels.second));
        }

        // Draw horizontal lines
        for (size_t y = 0; y <= _grid.second; ++y) {
            SDL_RenderDrawLine(&renderer, 0, static_cast<int>(y * cellHeight), static_cast<int>(_pixels.first), static_cast<int>(y * cellHeight));
        }
    }

    Dimensions _pixels, _grid;
};

class GameLoop {
public:
    GameLoop(SDL_Window* window, SDL_Renderer* renderer, const Grid& grid)
        : _window(window), _renderer(renderer), _grid(grid) {
    }

    void Run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            SDL_RenderClear(_renderer);

            _grid.Render(*_renderer);

            SDL_RenderPresent(_renderer);
        }
    }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    const Grid& _grid;
};

int main(int argc, char* argv[]) {
    SDLManager sdlManager;

    SDL_Window* window = sdlManager.CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = sdlManager.CreateRenderer(window, SDL_RENDERER_ACCELERATED);

    Grid grid(10, 10);
    grid.ChangeWindow(window);

    GameLoop gameLoop(window, renderer, grid);
    gameLoop.Run();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}

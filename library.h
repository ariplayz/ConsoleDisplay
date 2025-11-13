#ifndef CONSOLEDISPLAY_LIBRARY_H
#define CONSOLEDISPLAY_LIBRARY_H

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(__CYGWIN__)
  #if defined(BUILDING_MESON_LIBRARY)
    #define CONSOLEDISPLAY_API __declspec(dllexport)
  #else
    #define CONSOLEDISPLAY_API __declspec(dllimport)
  #endif
#else
  #define CONSOLEDISPLAY_API
#endif

namespace console_display {

class CONSOLEDISPLAY_API ConsoleDisplay {
public:
    static constexpr int WIDTH = 512;
    static constexpr int HEIGHT = 512;

    enum class CellType : std::uint8_t { Empty = 0, Pixel = 1, Text = 2 };

    struct Cell {
        CellType type{CellType::Empty};
        bool pixelOn{false};
        char ch{' '};
    };

    ConsoleDisplay();

    // Reset all cells to Empty
    void clear();

    // Set a cell to act like a pixel (on/off). Out-of-bounds are ignored.
    void setPixel(int x, int y, bool on = true);

    // Set a cell to show a text character. Out-of-bounds are ignored.
    void setText(int x, int y, char ch);

    // Write a string horizontally starting at (x,y). Stops at edge.
    void setTextString(int x, int y, const std::string& s);

    // Fill entire grid with pixel cells of the given on/off state.
    void fillPixels(bool on);

    // Get a copy of the cell at (x,y). If out-of-bounds, returns Empty.
    Cell getCell(int x, int y) const;

    // Convert the entire 512x512 grid to a printable string using the given
    // characters for pixel-on and empty cells.
    std::string toString(char pixelChar = '#', char emptyChar = ' ') const;

    // Render to an output stream (std::cout by default).
    void render(std::ostream& os) const;

private:
    static std::size_t index(int x, int y) { return static_cast<std::size_t>(y) * WIDTH + static_cast<std::size_t>(x); }
    static bool inBounds(int x, int y) { return x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT; }

    std::vector<Cell> m_cells; // size WIDTH*HEIGHT
};

} // namespace console_display

#endif // CONSOLEDISPLAY_LIBRARY_H

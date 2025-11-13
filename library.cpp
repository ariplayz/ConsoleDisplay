#include "library.h"

#include <algorithm>
#include <ostream>
#include <string>
#include <vector>

namespace console_display {

ConsoleDisplay::ConsoleDisplay()
    : m_cells(static_cast<std::size_t>(WIDTH) * static_cast<std::size_t>(HEIGHT)) {
    clear();
}

void ConsoleDisplay::clear() {
    for (auto& c : m_cells) {
        c.type = CellType::Empty;
        c.pixelOn = false;
        c.ch = ' ';
    }
}

void ConsoleDisplay::setPixel(int x, int y, bool on) {
    if (!inBounds(x, y)) return;
    auto& c = m_cells[index(x, y)];
    c.type = CellType::Pixel;
    c.pixelOn = on;
    c.ch = on ? '#' : ' ';
}

void ConsoleDisplay::setText(int x, int y, char ch) {
    if (!inBounds(x, y)) return;
    auto& c = m_cells[index(x, y)];
    c.type = CellType::Text;
    c.ch = ch;
    c.pixelOn = (ch != ' ');
}

void ConsoleDisplay::setTextString(int x, int y, const std::string& s) {
    if (y < 0 || y >= HEIGHT) return;
    int start = x < 0 ? 0 : x;
    int end = std::min(WIDTH, x + static_cast<int>(s.size()));
    for (int cx = start; cx < end; ++cx) {
        int si = cx - x;
        setText(cx, y, s[static_cast<std::size_t>(si)]);
    }
}

void ConsoleDisplay::fillPixels(bool on) {
    for (auto& c : m_cells) {
        c.type = CellType::Pixel;
        c.pixelOn = on;
        c.ch = on ? '#' : ' ';
    }
}

ConsoleDisplay::Cell ConsoleDisplay::getCell(int x, int y) const {
    if (!inBounds(x, y)) return Cell{}; // Empty default
    return m_cells[index(x, y)];
}

std::string ConsoleDisplay::toString(char pixelChar, char emptyChar) const {
    // Pre-allocate: WIDTH*HEIGHT chars + HEIGHT newlines
    std::string out;
    out.reserve(static_cast<std::size_t>(WIDTH + 1) * HEIGHT);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            const auto& c = m_cells[index(x, y)];
            char ch = emptyChar;
            switch (c.type) {
                case CellType::Pixel:
                    ch = c.pixelOn ? pixelChar : emptyChar;
                    break;
                case CellType::Text:
                    ch = c.ch;
                    break;
                case CellType::Empty:
                default:
                    ch = emptyChar;
                    break;
            }
            out.push_back(ch);
        }
        out.push_back('\n');
    }
    return out;
}

void ConsoleDisplay::render(std::ostream& os) const {
    os << toString();
}

} // namespace console_display

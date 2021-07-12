#include <array>
#include <optional>

class PacketBuffer
{
    std::array<uint8_t, 512> buffer;
    size_t                   pos;

   public:
    PacketBuffer() : buffer {}, pos { 0 } {};

   private:
    /// @param step amount to increment #pos by
    auto step(const size_t step) -> void { this->pos += step; }

    /// @param next_pos position to move #pos to
    auto seek(const size_t next_pos) -> void { this->pos = next_pos; }

    /**
     * @brief read a byte and increment #pos
     * @return std::optional<uint8_t>
     */
    auto read() -> std::optional<uint8_t>
    {
        if (this->pos > 512)
            return {};
        else
            return buffer[this->pos++];
    }

    /**
     * @brief read a byte
     * @return std::optional<uint8_t>
     */
    auto get() const -> std::optional<uint8_t>
    {
        if (this->pos > 512)
            return {};
        else
            return buffer[this->pos];
    }
};
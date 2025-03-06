# Pipelined Adder

This is a 4-stage pipelined **Multiply-and-Add** module designed with **ready-valid handshaking** for efficient data processing.

## Overview
The module performs `result = (in_a * in_b) + in_c` in a pipelined manner over **four stages**:

1. **Register Inputs:** Capture `in_a`, `in_b`, and `in_c`.
2. **Multiplication:** Compute `in_a * in_b`.
3. **Addition:** Add stored `c` value from the previous cycle.
4. **Output Stage:** Provide the final result.

It ensures seamless handshaking with `valid_in`, `ready_out`, `valid_out`, and `ready_in` signals.

---

## Block Diagram
![Pipeline Diagram](architecture.png)  
*(Replace `path/to/your/image.png` with the actual image path)*

---

## I/O Signals

| Signal      | Width  | Direction | Description |
|-------------|--------|-----------|-------------|
| `clk`       | 1-bit  | Input     | Clock signal |
| `reset`     | 1-bit  | Input     | Active-high reset |
| `in_a`      | 8-bit  | Input     | Multiplier operand |
| `in_b`      | 8-bit  | Input     | Multiplier operand |
| `in_c`      | 16-bit | Input     | Additive operand |
| `valid_in`  | 1-bit  | Input     | Input valid flag |
| `ready_out` | 1-bit  | Output    | Ready to accept new data |
| `result`    | 16-bit | Output    | Computed output `(a * b) + c` |
| `valid_out` | 1-bit  | Output    | Output valid flag |
| `ready_in`  | 1-bit  | Input     | Downstream ready signal |

---

## Operation

- New data is accepted when **`valid_in` & `ready_out` are high**.
- Computation occurs across **4 clock cycles**.
- `valid_out` indicates when the result is ready.
- Ready-valid handshake ensures seamless pipelined operation.

### Example Waveform


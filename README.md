# OS Memory Management & Demand Paging Simulator

A high-performance C++ simulation of an Operating System's Memory Management Unit (MMU). This project simulates virtual-to-physical address translation, caching via a **Translation Lookaside Buffer (TLB)**, and multiple page replacement strategies to analyze **Effective Access Time (EAT)**.

## 🚀 Features
- **Hierarchical Lookup:** Simulates the path: `TLB -> Page Table -> RAM -> Disk`.
- **Page Replacement Algorithms:**
  - **FIFO (First-In-First-Out):** Basic queue-based eviction.
  - **LRU (Least Recently Used):** High-performance eviction based on access history.
  - **OPT (Optimal):** "Clairvoyant" algorithm that minimizes faults by looking ahead at the trace.
- **Performance Metrics:** Reports TLB hit rates, Page hit rates, Page Faults, and Disk Writes (Dirty Bit management).
- **Hardware Simulation:** Configurable RAM size, Page size, and component latencies (in ns).

## 📂 Project Structure
To maintain a clean architecture, the code is organized as follows:
- `Main.cpp`: Entry point and basic argument handling.
- `/algorithms`: Logic for FIFO, LRU, and OPT replacement.
- `/memory`: Components for TLB, PageTable, and Address translation.
- `/simulator`: The core engine that runs the memory traces.
- `/config`: Configuration loader for hardware parameters.

## 💻 How to Run

### 1. Compilation
Use `g++` to compile all project modules:
```bash
g++ -o simulator Main.cpp config/*.cpp simulator/*.cpp memory/*.cpp -I.
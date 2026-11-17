# Codeforces C++ + Neovim Setup (`g++` + `clangd`)

## Filesystem Layout

```text
.
├── .competitest.lua     # Project-local competitest.nvim config (g++ C++17, 256MB stack, build/ output)
├── .clang-format        # Optional formatting rules
├── compile_flags.txt    # Configures clangd for every .cpp file (-std=c++17, -DLOCAL, -Wall, -Wextra)
├── template.cpp         # Codeforces C++17 template (fast I/O, LOCAL-only debug() macro)
├── problems/            # Active contest problems live here (e.g. a.cpp, b.cpp, c.cpp)
├── build/               # Compiled .exe binaries go here (gitignored)
├── testcases/           # Sample inputs/outputs managed by competitest.nvim (gitignored)
├── io/                  # Manual stdin/stdout scratch files (`input.txt`, `output.txt`)
├── archive/             # Move finished contests here so problems/ stays clean
└── scripts/
    ├── new.ps1          # Create `problems/<name>.cpp` from `template.cpp`
    ├── run.ps1          # Compile & run `problems/<name>.cpp` with `io/input.txt` (`-Sanitize` optional)
    └── archive.ps1      # Move `problems/*.cpp` and `testcases/` into `archive/<contest>/`
```

---

## Neovim Plugins Needed for Codeforces

### 1. Core Competitive Programming Runner (Required)
- **[`xeluxee/competitest.nvim`](https://github.com/xeluxee/competitest.nvim)** (depends on **`MunifTanjim/nui.nvim`**)
- **Browser Extension:** **Competitive Companion** (Chrome / Firefox)

This repo already includes `.competitest.lua`, so `competitest.nvim` automatically:
- Receives single problems or full Codeforces contests into `problems/` using `template.cpp`
- Stores sample testcases in `testcases/`
- Compiles with `g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -DLOCAL -Wl,--stack,268435456` into `build/` and diffs outputs in a split UI

```lua
{
  "xeluxee/competitest.nvim",
  dependencies = "MunifTanjim/nui.nvim",
  cmd = "CompetiTest",
  keys = {
    { "<leader>cr", "<cmd>CompetiTest run<cr>", desc = "CompetiTest Run" },
    { "<leader>cp", "<cmd>CompetiTest receive problem<cr>", desc = "Receive Problem" },
    { "<leader>cc", "<cmd>CompetiTest receive contest<cr>", desc = "Receive Contest" },
    { "<leader>ca", "<cmd>CompetiTest add_testcase<cr>", desc = "Add Testcase" },
    { "<leader>ce", "<cmd>CompetiTest edit_testcase<cr>", desc = "Edit Testcase" },
  },
  config = function()
    require("competitest").setup({
      local_config_file_name = ".competitest.lua",
    })
  end,
}
```

### 2. `clangd` Setup with MSYS2 `g++` (Important!)
Since your compiler is `C:\msys64\ucrt64\bin\g++.exe`, pass `--query-driver` to `clangd` in your LSP config so `clangd` resolves `<bits/stdc++.h>` and GCC's C++17 standard headers without false errors:

```lua
-- In nvim-lspconfig / Neovim 0.11+ vim.lsp.config("clangd", ...)
cmd = {
  "clangd",
  "--background-index",
  "--clang-tidy",
  "--query-driver=C:/msys64/ucrt64/bin/g++.exe",
}
```
And make sure `nvim-treesitter` has the `cpp` parser installed (`:TSInstall cpp`).

### 3. Fast Codeforces Submission Copy
Enable system clipboard in `init.lua`:
```lua
vim.opt.clipboard = "unnamedplus"
```
Then `:%y+` copies the entire `.cpp` file to your clipboard for pasting into Codeforces.

### 4. Optional (Nice to Have)
- **[`L3MON4D3/LuaSnip`](https://github.com/L3MON4D3/LuaSnip)** for C++ competitive programming snippets (DSU, SegTree, ModInt, Dijkstra, etc.)
- **[`akinsho/toggleterm.nvim`](https://github.com/akinsho/toggleterm.nvim)** for a quick floating terminal
- **[`mfussenegger/nvim-dap`](https://github.com/mfussenegger/nvim-dap)** + **`rcarriga/nvim-dap-ui`** + `codelldb` / `gdb` (if you want breakpoints beyond `debug(...)`)

---

## Workflow

1. Open Neovim in this repo root (`nvim .`).
2. Run `:CompetiTest receive contest` (or `:CompetiTest receive problem`), then click the **Competitive Companion** icon on Codeforces.
3. Edit `problems/<problem>.cpp`, then press `<leader>cr` (`:CompetiTest run`) to compile and test all sample cases.
4. Copy with `:%y+` and submit on Codeforces (`debug(...)` compiles to a no-op on Codeforces since `-DLOCAL` is not defined there).
5. Archive after the contest:
   ```powershell
   .\scripts\archive.ps1 cf_round_950
   ```

### Manual CLI Workflow
```powershell
.\scripts\new.ps1 a
# put sample input in io\input.txt
.\scripts\run.ps1 a
```

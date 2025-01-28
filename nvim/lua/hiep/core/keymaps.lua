-- set leader key to space
vim.g.mapleader = " "

local keymap = vim.keymap -- for conciseness

---------------------
-- General Keymaps -------------------

-- use jk to exit insert mode
keymap.set("i", "jk", "<ESC>", { desc = "Exit insert mode with jk" })

-- clear search highlights
keymap.set("n", "<leader>nh", ":nohl<CR>", { desc = "Clear search highlights" })

-- delete single character without copying into register
-- keymap.set("n", "x", '"_x')

-- increment/decrement numbers
keymap.set("n", "<leader>+", "<C-a>", { desc = "Increment number" }) -- increment
keymap.set("n", "<leader>-", "<C-x>", { desc = "Decrement number" }) -- decrement

----------------------------------------------------------------------------------
-- CP keymap
-- Create code block 
keymap.set('i', '{<CR>', '{<CR>}<Esc>O', { noremap = true, silent = true })

-- select all code
keymap.set('n', '<C-a>', '<esc>ggVG<CR>', { noremap = true, silent = true })

-- Set makeprg for C++ to compile with g++ directly
vim.opt.makeprg = "g++ -DDEBUG -lm -x c++ -Wall -Wextra -O2 -std=c++20 -o %:r %"
-- call quickfix window whenever we run :make
vim.api.nvim_create_autocmd("QuickFixCmdPost", {
    pattern = "[^l]*",  -- triggers after commands like :make, but not :lmake
    callback = function()
        if vim.tbl_count(vim.fn.getqflist()) > 0 then
            vim.cmd("cw")
        end
    end,
})
-- -- C++ filetype settings
vim.api.nvim_create_autocmd("FileType", {
    pattern = "cpp",
    callback = function()
        -- Define the 'Build' command
        vim.api.nvim_create_user_command('Build', function()
            -- Force-save the file and run make
            vim.cmd('w! | make')
        end, {})

        -- Define the 'Run' command
        vim.api.nvim_create_user_command('Run', function()
            -- Open a terminal to run the compiled program
            -- vim.cmd('vertical rightbelow 20split | terminal ./%:r')
            vim.cmd('horizontal rightbelow 20split | terminal ./%:r')
            vim.cmd([[startinsert]])
        end, {})
        -- -- Orun in outside terminal
        vim.api.nvim_create_user_command('Orun', function()
            local executable_path = vim.fn.expand('%:p:r')  -- Gets the full path without extension 
            local tmux_command = "tmux new-window 'bash -c \"" .. executable_path .. "; read -p \\\"\nPress Enter to close...\\\"\"'"
            vim.fn.system(tmux_command)
        end, {})

        -- Set keymaps to the new 'Build' and 'Run' commands
        vim.keymap.set("n", "<F9>", ":Build<CR>", { noremap = true, silent = true })
        vim.keymap.set("n", "<F10>", ":Run<CR>", { noremap = true, silent = true })
    end
})

vim.api.nvim_create_autocmd("FileType", {
    pattern = "python", -- Correct the file type pattern to 'python'
    callback = function()
        -- Define the 'BuildPy' command
        vim.api.nvim_create_user_command('BuildPy', function()
            -- Save the file and run it with python3
            vim.cmd('w!')
            vim.cmd('!python3 %')
        end, {})

        -- Define the 'RunPy' command
        vim.api.nvim_create_user_command('RunPy', function()
            -- Open a terminal to run the Python script
            vim.cmd('w!') -- Ensure the file is saved before running
            vim.cmd('horizontal rightbelow 20split | terminal python3 %')
            vim.cmd('startinsert')
        end, {})
    end
})

-- Autocommand that inserts the debugging template into new C++ files
vim.api.nvim_create_autocmd("BufNewFile", {
    pattern = "*.cpp",
    callback = function()
        vim.cmd('0r ' .. vim.fn.expand('/Volumes/E/CS/CP/cpplib/template.cpp'))
        vim.cmd('normal G')
    end
})
--------------------------------------------------------------------------------
-- Zathura new command
vim.api.nvim_create_autocmd("FileType", {
    pattern = "tex",
    callback = function()
        -- Define the 'OpenPdf' command to open PDF with Zathura
        vim.api.nvim_create_user_command('OpenPdf', function()
            local tex_file_path = vim.fn.expand('%:p')  -- Get the current file path
            local pdf_file_path = tex_file_path:gsub("%.tex$", ".pdf")  -- Change extension to .pdf
            vim.cmd('!zathura "' .. pdf_file_path .. '" &> /dev/null &')  -- Execute Zathura command in the background
        end, {desc = 'Open the PDF version of the current TeX file in Zathura'})
    end
})

-- window management
keymap.set("n", "<leader>sv", "<C-w>v", { desc = "Split window vertically" }) -- split window vertically
keymap.set("n", "<leader>sh", "<C-w>s", { desc = "Split window horizontally" }) -- split window horizontally
keymap.set("n", "<leader>se", "<C-w>=", { desc = "Make splits equal size" }) -- make split windows equal width & height
keymap.set("n", "<leader>sx", "<cmd>close<CR>", { desc = "Close current split" }) -- close current split window

keymap.set("n", "<leader>to", "<cmd>tabnew<CR>", { desc = "Open new tab" }) -- open new tab
keymap.set("n", "<leader>tx", "<cmd>tabclose<CR>", { desc = "Close current tab" }) -- close current tab
keymap.set("n", "<leader>tn", "<cmd>tabn<CR>", { desc = "Go to next tab" }) --  go to next tab
keymap.set("n", "<leader>tp", "<cmd>tabp<CR>", { desc = "Go to previous tab" }) --  go to previous tab
keymap.set("n", "<leader>tf", "<cmd>tabnew %<CR>", { desc = "Open current buffer in new tab" }) --  move current buffer to new tab
-- keymap.set("i", "(", ""()"<Left>") --  move current buffer to new tab
keymap.set('i', '"', '""<Left>')
keymap.set('i', '(', '()<Left>')
keymap.set('i', '{', '{}<Left>')
keymap.set("i", "$","$$<Left>")
keymap.set('i', '[', '[]<Left>')

-- for adding template 
keymap.set('n', 'dsu', ':r /Volumes/E/CS/CP/DSA/SubProblem/dsu.cpp<CR>', { noremap = true, silent = true })
keymap.set('n', 'lst', ':r /Volumes/E/CS/CP/DSA/SubProblem/lazySegmentTree.cpp<CR>', { noremap = true, silent = true })
keymap.set('n', 'st', ':r /Volumes/E/CS/CP/DSA/SubProblem/segmentTree.cpp<CR>', { noremap = true, silent = true })
keymap.set('n', 'ft', ':r /Volumes/E/CS/CP/DSA/SubProblem/fenwickTree.cpp<CR>', { noremap = true, silent = true })
keymap.set('n', 'dbg', ':r /Volumes/E/CS/CP/cpplib/template.cpp<CR>', { noremap = true, silent = true })


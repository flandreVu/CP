return {
   {
        'sainnhe/everforest',
        lazy = false,  -- This line is typically unnecessary for `packer.nvim`, as it's not a recognized field
        priority = 1000,
        config = function()
            -- Configuration settings specific to everforest
            if vim.fn.has('termguicolors') == 1 then
                vim.o.termguicolors = true
            end
            vim.o.background = 'dark'
            vim.g.everforest_background = 'medium'
            -- vim.g.everforest_enable_italic = 1
            vim.g.everforest_better_performance = 1

            -- Activate the colorscheme
            vim.cmd("colorscheme everforest")
            -- Activate the colorscheme
            vim.cmd("colorscheme everforest")
        end
    }
}

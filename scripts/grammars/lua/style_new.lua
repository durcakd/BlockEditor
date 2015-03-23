local NORMAL_TEXT = {
    item = true,
    object = "text",
    text = {
        isColor = false,
    }
}

local function COLOR_TEXT(color)
    return {
        item = true,
        object = "text",
        text = {
            isColor = true,
            color = color
        }
    }
end

local function COLOR_BOLD_TEXT(color)
    return {
        item = true,
        object = "text",
        text = {
            isColor = true,
            color = color
        }
    }
end

local VERT_BLOCK = {
    grid = true,
    object = "vertical"
}

local LINE = {
    grid = true,
    object = "horizontal"
}

local FUNCTIONDEF = {
    grid = true,
    object = "vertical"
}

local CYCLE = {
    item = true,
    object = "vertical"
}

local FUNCTION_STAT = {
    grid = true,
    object = "horizontal"
}

return {
        root = VERT_BLOCK,
        block = VERT_BLOCK,
        do_stat = VERT_BLOCK,
        if_stat = VERT_BLOCK,
        while_stat = VERT_BLOCK,
        repeat_stat = VERT_BLOCK,
        for_stat = VERT_BLOCK,


	header = LINE,
	par_list = LINE,
	dot_comma = LINE,
	assing_stat = LINE,
	functioncall_stat = LINE,
	label_stat = LINE,
	break_stat = LINE,
	goto_stat = LINE,
	return_stat = LINE,
	exp = LINE,

	keyword = COLOR_BOLD_TEXT({ 0, 0, 1 }),
	operator = COLOR_BOLD_TEXT({ 1, 0, 1 }),
	comment = COLOR_TEXT(0.5),

	Name = NORMAL_TEXT,
	Number = COLOR_BOLD_TEXT({ 0, 0.8, 0 }),
	String = COLOR_TEXT({ 1, 0, 0 }),

        function_stat = FUNCTION_STAT,
        functiondef = FUNCTIONDEF,
        cycle = CYCLE
}

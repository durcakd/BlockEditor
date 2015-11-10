local NORMAL_TEXT = {
    item = true,
    object = "text",
    grid = false,
    text = {
        isColor = false
    }
}

local function COLOR_TEXT(color)
    return {
        item = true,
        object = "text",
        grid = false,
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
        grid = false,
        text = {
            isColor = true,
            isBold = true,
            color = color
        }
    }
end

local function VERT_BLOCK(color)
    return {
        grid = true,
        object = "vertical",
        context = true,
        background = {
            color = color or {0,0,0,0}
        }
    }
end

local function LINE(color)
    return {
        grid = true,
        object = "horizontal",
        background = {
            color = color or {0,0,0,0}
        }
    }
end

local function TRANSPARENT_BLOCK(orientation)
    return {
        grid = true,
        object = orientation or "vertical",
        transparent = true
    }
end

local CYCLE = {
    item = true,
    object = "vertical"
}

return {
        root = TRANSPARENT_BLOCK("vertical"),
        block = TRANSPARENT_BLOCK("vertical"),
        do_stat = VERT_BLOCK({0.5, 0.5, 1.0, 0.1}),
        if_stat = VERT_BLOCK({1, 0.8, 0, 1}),
        while_stat = VERT_BLOCK({1, 0.6, 0.6, 1}),
        repeat_stat = VERT_BLOCK({1, 0.6, 0.6, 1}),
        for_stat = VERT_BLOCK({1, 0.3, 0.3, 1}),


	header = LINE(),
	par_list = LINE(),
	dot_comma = LINE(),
        assing_stat = LINE({0.5, 0.8, 1, 1}),
        functioncall_stat = LINE({0.5, 0.8, 1, 1}),
	label_stat = LINE(),
	break_stat = LINE(),
	goto_stat = LINE(),
        return_stat = LINE({0.5, 0.8, 1, 1}),
        exp = LINE(),

        keyword = COLOR_BOLD_TEXT({ 0, 0, 1 }),
        operator = COLOR_BOLD_TEXT({ 1, 0, 1 }),
        comment = COLOR_TEXT({ 0.4, 0, 0 }),

	Name = NORMAL_TEXT,
        Number = COLOR_BOLD_TEXT({ 0, 0.8, 0 }),
        String = COLOR_TEXT({ 1, 0, 0 }),

        function_stat = VERT_BLOCK({0.75,0.6,0.75,1}),
        functiondef = VERT_BLOCK({0.3,1,0.3,0.5}),
        cycle = CYCLE
}

print "Initializing core"

local parser = require 'parser'
--local compare = require 'compare'
--local utils = require 'utils'

--- Load grammar and style
-- Must be called to initialize lua state
-- @param name
function loadGrammarAndStyle(name)
	print("Loading grammar and style: " .. name)

	local grammar = require(string.format("grammars.%s.grammar", name))
        currentActiveStyle = require(string.format("grammars.%s.style_new", name))
        currentActiveParser = parser.create(grammar, currentActiveStyle)

	local sep = "/"
	currentGramarBasePath = "scripts"..sep.."grammars"..sep..name..sep

	print("Grammar and style '" .. currentGramarBasePath .. "' successfully loaded.")
end

--- Parse new text
-- You can call it to initialize AST also to parse new text
-- @param newText
-- TODO:
-- @returns Last parsed character

function parseTextNew(newText)
    print ("\nParsing text ===============================")
    local newTree = parseNew(currentActiveParser, newText,
        -- Add Item
        function(index, element, parent)
            --print('ADD ITEM: ' .. element.type .. ' "' .. tostring(element.value) .. '" at index ' .. tostring(index) .. ' to parent[' .. tostring(parent) .. '] ')
            element.instance = addBasicItem( element.type, element.value, parent.instance, index)
        end,

        -- Add Grid
        function(index, element, parent)
            --print('ADD GRID: ' .. element.type .. ' "' .. tostring(element.value) .. '" at index ' .. tostring(index) .. ' to parent[' .. tostring(parent) .. '] ')
            element.instance = addBasicLayout( element.type, parent.instance, index)
        end
        )
end

function loadStyles()
    print ("\nLoad styles ===============================")
    for k,v in pairs(currentActiveStyle) do
        if type(v) == "table" then
            print ( k.." >>  "..v.object)
            local isItem = v.item or false;
            local isLayout = v.grid or false;
            local isColor = (type(v.text) == "table" and type(v.text.color) )  or false;

            addStyle(v, k)
        end
    end
end

function parseNew(parser, text, addItemFnc, addGridFnc)
    print("PARSE AST **************************************")
    addItem = addItemFnc
    addGrid = addGridFnc
    local newTree = parser:match(text)

    local parsedCharacters = 0

    if newTree ~= nil and #newTree > 0 then
        parsedCharacters = newTree[#newTree].positionEnd
    end

    if #text + 1 ~= parsedCharacters then
        -- if grammar failed to parse whole tree, return error
        print ('Parsed ' .. tostring(parsedCharacters) .. ' characters, ')
        print 'reparsing done with error!\n'
        return nil, parsedCharacters
    end

    local root = { type = 'root' , value = newTree }

    --printTree(nil, root, " ")

    print "ADDING ......."
    sendNode(1, root, {});

end

function sendNode( index, node, parent)
    print (">>> ".. index .."    "..tostring(node) .. "  " .. tostring(parent))
    if node ~= nil and type(node) == "table" then
        if node.value ~= nil and type(node.value) == "table" then
            addGrid(index, node, parent)
            -- children
            for k,v in pairs(node.value) do
                sendNode( k, v, node)
            end
        else
            addItem(index, node, parent)
        end
    end
end

function printTree(key, value, u)
    if value ~= nil then
        if type(value) == "table" then

            printTable( value, u)

            for k,v in pairs(value) do
                if type(v) == "table" then
                    print (">-  "..u.."  "..k)
                    printTree(k,v, u.."-")
                end
            end
        else
            --print ( ">   "..u, key , value)
        end
    end
end

function printTable(value, u)
    if type(value) == "table" then
            for k,v in pairs(value) do
                if type(v) ~= "table" then
                    print (">>  "..u.."  "..k.." >".. v.."<" )
                end
            end
    end
end

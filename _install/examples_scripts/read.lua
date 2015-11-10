m = io.read()
if m=='r' then
    m = io.read()
elseif m=='p' then
    print('-- ' .. m)
elseif m=='x' then
    print('++ ' .. m)
else
    print(m)
end


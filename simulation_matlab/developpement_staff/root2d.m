function F = root2d(teta)

angle_bloque = evalin('base', 'angle_bloque');

if angle_bloque == 1
    p1_x = evalin('base', 'p1_x');
    p1_y = evalin('base', 'p1_y');
elseif angle_bloque == 2
    p2_x = evalin('base', 'p2_x');
    p2_y = evalin('base', 'p2_y');
else
    p3_x = evalin('base', 'p3_x');
    p3_y = evalin('base', 'p3_y');
end

d1 = evalin('base', 'd1');
d2 = evalin('base', 'd2');
d3 = evalin('base', 'd3');
x_desire = evalin('base', 'x_desire');
y_desire = evalin('base', 'y_desire');

if angle_bloque == 1
    F(1) = p1_x + d2*cos(teta(1)) + d3*cos(teta(2)) - x_desire;
    F(2) = p1_y + d2*sin(teta(1)) + d3*sin(teta(2)) - y_desire;
elseif angle_bloque == 2
    F(1) = d1*cos(teta(1)) + p2_x + d3*cos(teta(2)) - x_desire;
    F(2) = d1*sin(teta(1)) + p2_y + d3*sin(teta(2)) - y_desire;
else
    F(1) = d1*cos(teta(1)) + d2*cos(teta(1)) + p3_x - x_desire;
    F(2) = d1*sin(teta(1)) + d2*sin(teta(1)) + p3_y - y_desire;
end

end


function F = root2d_v2(teta)



d1 = evalin('base', 'd1');
d2 = evalin('base', 'd2');
d3 = evalin('base', 'd3');
x_desire = evalin('base', 'x_desire');
y_desire = evalin('base', 'y_desire');


F(1) = d1*cos(teta(1)) + d2*cos(teta(2)) + d3*cos(teta(3)) - x_desire;
F(2) = d1*sin(teta(1)) + d2*sin(teta(2)) + d3*sin(teta(3)) - y_desire;


end



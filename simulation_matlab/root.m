function F = root(teta)

moteur_bloque = evalin('base', 'moteur_bloque');

switch(moteur_bloque)
    case 1
        p_x = evalin('base', 'p1_x');
        p_y = evalin('base', 'p1_y');
    case 2
        p_x = evalin('base', 'p2_x');
        p_y = evalin('base', 'p2_y');
    case 3
        p_x = evalin('base', 'p3_x');
        p_y = evalin('base', 'p3_y');
end




d1 = evalin('base', 'd1');
d2 = evalin('base', 'd2');
d3 = evalin('base', 'd3');

x_desire = evalin('base', 'x_desire');
y_desire = evalin('base', 'y_desire');


F(1) = p_x + d2*cos(teta(1)) + d3*cos(teta(2)) - x_desire;
F(2) = p_y + d2*sin(teta(1)) + d3*sin(teta(2)) - y_desire;



end

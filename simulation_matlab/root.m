function F = root(teta)

moteur_bloque = evalin('base', 'moteur_bloque');
x_desire = evalin('base', 'x_desire');
y_desire = evalin('base', 'y_desire');
switch(moteur_bloque)
    case 1
        p_x = evalin('base', 'p1_x');
        p_y = evalin('base', 'p1_y');
        d1 = evalin('base', 'd1');
        d2 = evalin('base', 'd2');
        d3 = evalin('base', 'd3');
        
        F(1) = p_x + d2*cos(teta(1)) + d3*cos(teta(2)) - x_desire;
        F(2) = p_y + d2*sin(teta(1)) + d3*sin(teta(2)) - y_desire;
    case 2
        rayon = evalin('base','rayon');
        d3 = evalin('base', 'd3');
        
        F(1) = rayon*cos(teta(1))+d3*cos(teta(2)) - x_desire;
        F(2) = rayon*sin(teta(1))+d3*sin(teta(2)) - y_desire;
            
    case 3
        p_x = evalin('base', 'p3_x');
        p_y = evalin('base', 'p3_y');
end











end

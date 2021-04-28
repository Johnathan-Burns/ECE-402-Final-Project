

disp("START")

%position of base station/reciever 1 relative to rocket
px1=0;
py1=100;
pz1=0;
%position of base station/reciever 2 relative to rocket
px2=100;
py2=0;
pz2=0;
%position of base station/reciever 3 relative to rocket
px3=-100;
py3=0;
pz3=0;

%freqency recorded by the 3 recievers(this will need to be vector or matrix
%table)
fr1=433999612;
fr2=433999612;
fr3=433999612;

%frequency transmitted from rocket
fs= 434000000;

%velocity of radio(speed of light)
c= 299792458;

%time between frequency measurements(will be part of the frequency vector)
t=1;

%calculating relative velocity from each base station using doppler shift
v1=((fs*c)-(fr1*c))/fr1;
v2=((fs*c)-(fr2*c))/fr2;
v3=((fs*c)-(fr3*c))/fr3;

%calculation of relative position change
d1=v1*t;
d2=v2*t;
d3=v3*t;

disp("relative velocity from base station 1")
disp(v1);
disp("relative velocity from base station 2")
disp(v2);
disp("relative velocity from base station 3")
disp(v3);



%Solving system of equations for 3-D corridinates
syms x y z
eqn1=(x-px1)^2+(y-py1)^2+(z-pz1)^2==d1;
eqn2=(x-px2)^2+(y-py2)^2+(z-pz2)^2==d2;
eqn3=(x-px3)^2+(y-py3)^2+(z-pz3)^2==d3;
sol = solve([eqn1, eqn2, eqn3], [x, y, z]);
xSol = sol.x;
xSol=round(xSol);
ySol = sol.y;
ySol=round(ySol);
zSol = sol.z;
zSol=round(zSol);

disp("X-coordinate of rocket");
disp(xSol);
disp("Y-coordinate of rocket");
disp(ySol);
disp("Z-coordinate of rocket");
disp(zSol);


%updated position of base station/reciever 1 relative to rocket
px1=px1-xSol;
py1=py1-ySol;
pz1=pz1-zSol;
%updated position of base station/reciever 2 relative to rocket
px2=px2-xSol;
py2=py2-ySol;
pz2=pz2-zSol;

%updated position of base station/reciever 3 relative to rocket
px3=px3-xSol;
py3=py3-ySol;
pz3=pz3-zSol;


disp("Updated position of base station/reciever 1 relative to rocket(XYZ)")
disp(px1);
disp(py1);
disp(pz1);
disp("Updated position of base station/reciever 2 relative to rocket(XYZ)")
disp(px2)
disp(py2)
disp(pz2)
disp("Updated position of base station/reciever 3 relative to rocket(XYZ)")
disp(px3)
disp(py3)
disp(pz3)


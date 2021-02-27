%Okay, so basically this is the game snake. You move the lil guy using
%WASD and then when you hit the food you eat it and get bigger but if u run
%into yourself you die.

clc
clear
close all

%SETUP ----------------------------------------------------------------
%Every good play starts by setting the scene and this masterpiece is no
%different
snake_scene=simpleGameEngine('img.png',16,16,1,[0,0,0]);
framerate=15;
%^Shoutout to 15 fps btw, pretty good if im being honest
maxSize=50; %Board size (maxSize x maxSize)
map= zeros(maxSize); %Map is a numerical representation of the board.
%each number corresponds to it's location on img.png
map=map+30; %30 is a blank space 
%SETUP COMPLETE ----------------------------------------------------------


%hisssssssssss (Snake btw) ------------------------------------------------
%snake finna be a 2d array of positions UWU
Snake=[25 25
       24 25
       23 25];%Snek starts at 3 units long.
Snake_Anim_State=19; %first snake head on tile 19 of img.png
Anim_hold=5; %number of frames to hold each animation
Anim_hold_state=0;%This is a value that will change the anim_state once it exceeds the hold value
Snake_body_img=31;%The snake body image (solid dark green) is on tile 31 
Direction= [1,0];%Direction [y,x]
global alive
alive =1;%MY MAKESHIFT BOOLEAN TM
global teleportOnEdge
teleportOnEdge=0;%boolean: if 0 will kill player on edge, if 1 will teleport player to other side
%Death sounds
%Stuff for the mario death sound
[y, Fs] = audioread('death.mp3');
death=audioplayer(y, Fs);
%Stuff for scream on death
[y3, Fs3] = audioread('scream.mp3');
scream=audioplayer(y3, Fs3);
%END OF SNAKE STUFF (unhissssssssssssssssss) ------------------------------

%RANDOM LOBBY MANAGEMENT STUFF--------------------------------------------
%Game music
[y2, Fs2] = audioread('kahoot_lobby_music.mp3');
lobby=audioplayer(y2, Fs2);
%END LOBBY STUFF ----------------------------------------------------------


%FOOD STUFF---------------------------------------------------------------
%NOMNOMNOM
food=[1,1];
food=newFood(maxSize);
Grow=0;
%Eat sound
[y4, Fs4] = audioread('NOMNOMNOM.mp3');
Nom=audioplayer(y4, Fs4);
%FED----------------------------------------------------------------------


%NOW WE CAN ACTUALLY PLAY YAY. I'M SO EXCITED HYPERS!!!!!!!!!!
%-------------------------------------------------------------------------
while(alive==1) %The game runs while you are alive (big brain)
    play(lobby);%Basically while you're alive it plays the lobby music
    %also it doesnt play it on top of itself which is p cool because that
    %made this a lot less annoying to set up
    tic; 
    
    %GROW OR UPDATE-------------------------------------------------------
    %Grow is a janky boolean that I made, cause this is easier than 
    %programming like an actual intelligent human being with knowledge
    %developed after the bronze age.
    %If this wasn't matlab this whole thing would be object oriented and 
    %done using a grow function but doing that here was just more trouble
    %than it was worth because It's only a minor deviation from update(tm)
    %and I already wrote a function for that.
    if Grow ~=1 
        %basically if it's not growing then you just update the position
        Snake=updateSnake(Snake,Direction,maxSize);
    else
        %but if it is growing you save the last position
        Save=Snake(length(Snake),:);
        %then you update the position
        Snake=updateSnake(Snake,Direction,maxSize);
        %and you append the last position to the end of the position matrix
        Snake(length(Snake)+1,:)=Save;
        %and then you set grow back to 0(false)
        Grow=0;
    end
    %GLAD THATS OVER WITH-------------------------------------------------
    
    %DRAW ^_^, it um... draws the thing, Also shoutout to the function call
    drawScene(snake_scene,drawMap(maxSize,Snake_Anim_State,Snake,Snake_body_img,food));
    
    %ANIMATE DAT BOI ------------------------------------------------------
    %So Anim_hold corresponds to the number of frames that we hold on each
    %animation because if you animate a small image with minor differences
    %really fast it is unnoticable so we need to stay on each frame of the
    %animation longer than 1 frame.
    %Anim_hold_state is essentially a frame counter that updates every
    %frame.
    if Anim_hold_state>Anim_hold 
        %if the counter is greater than the hold then we update the
        %animation frame 
        Snake_Anim_State=Snake_Anim_State+1;
        %and reset the counter to 0
        Anim_hold_state=0;
    else
        %if the counter is less than the hold then we just incriment it
        Anim_hold_state=Anim_hold_state+1;
    end
    if Snake_Anim_State>23 %23 is the last frame(open mouth)
        %if it exceeds the last frame it resets to the beginning of the
        %loop
        Snake_Anim_State=19;
    end
    %WOW THE HEAD CHANGES COLOR AND THE MOUTH OPENS AND CLOSES ^_^
    %----------------------------------------------------------------------
    
    %SNAKE LIEK FOOD -----------------------------------------------------
    %if the snake's head is in the same position as the food then it eats
    if Snake(1,1)==food(1) && Snake(1,2)==food(2)
        %Eating means the snake grows so our janky grow boolean is set to
        %1(true)
        Grow=1;
        %then food is set to a new food created using a function(basically
        %just gives it a random location)
        food=newFood(maxSize);
        %and we play the eating sound.
        play(Nom);
    end
    %NOMNOMNOM------------------------------------------------------------
    
    %TURNING REEEEEEEEEEEEEE---------------------------------------------
    %k obtained by logging what key is held down
    k= guidata(snake_scene.my_figure);
    %all of these 'not' conditions are to keep the user from turning back
    %on themselves.
    if k=='a' & Direction ~= [0,1] %if the key is a
        Direction=[0,-1]; %Change direction to left
    elseif k=='s' & Direction ~= [-1,0] %if the key is s
       Direction=[1,0];%Change direction to down
    elseif k=='w' & Direction ~= [1,0]%if the key is w
        Direction=[-1,0];%Change direction to up
    elseif k=='d' & Direction ~= [0,-1]%if the key is d
        Direction=[0,1];%Change direction to right
    end
    %REEEEEEEEEEEEEE-------------------------------------------------------
    
    %SNAKES CAN DIE TOO :( ------------------------------------------------
    %we can check to see if the snake is dead by looping through all of
    %it's body segments(segment 2-end)
    for i=2:length(Snake)
        if Snake(1,:)==Snake(i,:)
            %if the position of the head is the same as the position of the
            %segment under test then set our alive boolean to 0(false) this
            %will effectively end the game.
            alive=0;
        end
    end 
    %ALEXA PLAY DESPACITO--------------------------------------------------
    
    pause(1/framerate-toc);
end
%GAME OVER----------------------------------------------------------------
%report the score in the command window
fprintf('GAME OVER: your score was %i\n',length(Snake)-3);
%stop playing the lobby music
stop(lobby);
%play a scream
play(scream);
%then play the sad death music :(
play(death);
%and close the game window.
close all;


%NEW FOOD FUNCTION---------------------------------------------------------
%Returns a new location for food
%param s- max size of the board
function f=newFood(s)
    %this just returns a new 2 term long array(for position) with randomly
    %generated values from 1 to s
    f=[randi(s,1),randi(s,1)];
end
%HUNGRY?-------------------------------------------------------------------

%DRAW MAP FUNCTION---------------------------------------------------------
%Recreates the map with the propper numbers corresponding to the location
%of each segment of the snake and the food
%param snake- a snake position matrix
%param Snake_Anim_State- the current image grid number corresponding to the
%   head of the snake
%param s- the max size of the board
%param Snake_body_img- the img grid number corresponding to the body
%param Food- food location as an array
function newMap=drawMap(s,Snake_Anim_State,Snake,Snake_body_img,Food)
    %Set the map to a s x s matrix of 30 because on img.png 30 corresponds
    %to a blank space [and'll write your name](shoutout to t-swift)
    map= zeros(s);
    map=map+30;
    
    %change the number at the position of the snake's head from 30 to the
    %value given by Snake_Anim_State
    map(Snake(1,1),Snake(1,2))=Snake_Anim_State;
  
    %loop through the remainder of the snake(one could call this the
    %snake's body, because that's what it is)
    for i=2:length(Snake)
        %set each location that the snake's body is at to a solid green
        %tile
        map(Snake(i,1),Snake(i,2))=Snake_body_img;
    end
    %Place the food image on the position of the food
    map(Food(1),Food(2))=32;
    %return statement
    newMap=map;
end
%BETTER CARTOGROPHERS THAN MIDIEVAL SPAIN
%--------------------------------------------------------------------------

%UPDATE SNAKE FUNCTION-----------------------------------------------------
%this function basically moves the snake
%param s- a snake (position matrix)
%param d- a direction array
%param max- the max size of the window
function sn=updateSnake(s,d,max)
%Redeclaration of globals for edge behavior because matlab is weird
global alive
global teleportOnEdge
    %loop through the snake's position matrix backwards    
    for i=length(s):-1:2
        %set each segment to the segment before it. This effectively moves
        %the body forward on top of itself so that the final body segment
        %is located where the second to last body segment previously was
        %and the first body segment is located where the head was
        s(i,:)=s(i-1,:);
    end
    %move the head according to the direction array
    s(1,1)=s(1,1)+d(1);
    s(1,2)=s(1,2)+d(2);
    %SIDE BEHAVIORS-------------------------------------------------------
    %if teleportOnEdge=0 then the player dies at the edge, otherwise
    %teleport the player to the other side
    if s(1,1)>max 
        %if the snake's head is off of the top side then move it to the
        %bottom side
        s(1,1)=1;
        alive = teleportOnEdge;
    elseif s(1,1)<1
        %but if the snake's head is off the top side move it to the bottom
        %side
        s(1,1)=max;
        alive = teleportOnEdge;
    end
    if s(1,2)>max
        %and if the snake's head is off the right side move it to the left 
        %side 
       s(1,2)=1;
       alive = teleportOnEdge;
    elseif s(1,2)<1
        %But then if the snake's head is off the left side you should move
        %it to the right side
        s(1,2)=max;     
        alive = teleportOnEdge;
    end
   %THE SNAKE STAYS ON SCREEEN--------------------------------------------
    
    %this is a return statement to return our updates snake.
    sn=s;
    
end
%MOTION MADE EASY---------------------------------------------------------



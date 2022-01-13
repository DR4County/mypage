import greenfoot.*;  // (World, Actor, GreenfootImage, Greenfoot and MouseInfo)

/**
 * Write a description of class Duke here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Player extends Actor
{
    private int horizontalSpeed = 2, verticalSpeed = 10,
                horizontalVelocity = 0, verticalVelocity = 0,
                maxHorizontalVelocity = 5, maxVerticalVelocity = 10;
                
    private double horizontalVelocityIncrement = 1, verticalVelocityIncrement = 1;
    
    private String lastHorizontal, lastVertical,
                   previousHorizontal, previousVertical;
    
    private boolean jumping = false, loaded = false, facing = false; //False is left, and true is right;
    
    private long time = 0,
                systemTime = 0,
                timeOfJumping = 0,
                
                jumpHeight = 10,
                startHeightFromJump = 0;
                
    private double jumpDuration = 0.2;
    
    public String drawState = "idle";
    private MyWorld thisWorld = ((MyWorld) getWorld());
    
    /**
     * Act - do whatever the Duke wants to do. This method is called whenever
     * the 'Act' or 'Run' button gets pressed in the environment.
     */
    public Player(int width, int height){
        GreenfootImage image = getImage();
        image.scale(width, height); 
    }
    public void act() 
    {
        if (!loaded){
            loaded = true;
            thisWorld = ((MyWorld) getWorld());
        }
        checkKeys();
        updateSharedValues();
    }
    
    public void updateSharedValues(){
        MyWorld selectedWorld = (MyWorld) getWorld();
        time = selectedWorld.time;
        systemTime = selectedWorld.systemTime;
    }
    
    public void checkKeys()
    {
        checkDirectionChange();
        if (Greenfoot.isKeyDown("right"))
        {
            move("right");
        }
        
        if (Greenfoot.isKeyDown("left"))
        {
            move("left");
        } 
        checkCollision();
        
    }
    public boolean groundCollision(){
        return getOneObjectAtOffset(0, getImage().getHeight()/2, CollisionBlock.class) != null;
    }
    
    public boolean wallCollision(String direction){
        boolean collided = false;
        int checkX = 0, checkY = 0;

        if (direction == "up"){
        }
        if ((direction == "ground" || direction == "down")){
            checkY = getImage().getHeight()/2;
        }
        return (getOneObjectAtOffset(checkX, checkY, CollisionBlock.class)) != null;
    }
    
    public boolean collisionAt(int x, int y){
        Actor under = getOneObjectAtOffset(x, y, CollisionBlock.class);
        return under != null;
    }
    
    public void checkCollision(){
        //System.out.println(getImage().getHeight() / 2);
        
            
        if (wallCollision("ground") && jumping == false) {
            if (Greenfoot.isKeyDown("up")){
                jumping = true;
                timeOfJumping = System.currentTimeMillis();
                startHeightFromJump = getY();
                timeOfJumping = systemTime;
            }
        }
        else if (jumping && timeOfJumping < systemTime){
            double percentageOfJump = (systemTime - timeOfJumping) / (jumpDuration * 1000);
            long jumpY = getY() - (long) (jumpHeight * ( percentageOfJump));
            System.out.println(jumpY);
            if (startHeightFromJump + jumpHeight > jumpY && jumpY < startHeightFromJump + jumpHeight){
                setLocation (getX(),  (int) jumpY );
            }
            if (systemTime > timeOfJumping + ( jumpDuration * 1000 ) ){
                jumping = false;
                startHeightFromJump = 0;
                timeOfJumping = 0;
            }
        }
        else {
            move("down");
        }
    }
    
    public void checkDirectionChange (){
        if (lastHorizontal != previousHorizontal){
            resetVelocity("horizontal");
        }
        else if (lastVertical != previousVertical){
            resetVelocity("vertical");
        }
    }
    
    public void move(String direction){
        switch (direction){
            case "up":
                setLocation (getX(), getY() - verticalSpeed - verticalVelocity);
                increaseVelocity("vertical");
                previousVertical = lastVertical;
                lastVertical = "up";
                break;
                
            case "down":
                int maxFall = 0, nh =  + verticalSpeed + verticalVelocity;
                boolean maxFallFound = false;
                
                for ( int i = 1; maxFallFound == false; i++){
                    System.out.println(getImage().getHeight() / 2 + nh/i);
                    if (collisionAt(0, getImage().getHeight() / 2 + nh/i)) return;
                    if (!collisionAt(0, getImage().getHeight() / 2 + nh/i)){
                        maxFall = nh/i;
                        maxFallFound = true;
                    }
                }
                
                setLocation (getX(), getY() + (verticalSpeed + verticalVelocity) / maxFall);
                increaseVelocity("vertical");
                previousVertical = lastVertical;
                lastVertical = "down";
                break;
                
            case "left":
                setLocation (getX() - horizontalSpeed - horizontalVelocity, getY());
                increaseVelocity("horizontal");
                previousHorizontal = lastHorizontal;
                lastHorizontal = "left";
                if (facing == true){
                    facing = false;
                    getImage().mirrorHorizontally(); 
                }
                break;
                
            case "right":
                setLocation (getX() + horizontalSpeed + horizontalVelocity, getY());
                increaseVelocity("horizontal");
                previousHorizontal = lastHorizontal;
                lastHorizontal = "right";
                if (facing == false){
                    facing = true;
                    getImage().mirrorHorizontally(); 
                }
                break;
        }
    }
    public void increaseVelocity(String direction){
        switch (direction){
            case "vertical":
                if (verticalVelocity + verticalVelocityIncrement < maxVerticalVelocity){
                    verticalVelocity += verticalVelocityIncrement;
                }
                break;
                
            case "horizontal":
                if (horizontalVelocity + horizontalVelocityIncrement < maxHorizontalVelocity){
                    horizontalVelocity += horizontalVelocityIncrement;
                }
                break;
        }
    }
    
    public void changeDrawState(String state){
        drawState = state;
    }
    
    public void draw(){
        switch(drawState){
            case "idle":
                break;
        }
    }
    
    public void resetVelocity(String direction){
        switch (direction){
            case "vertical":
                verticalVelocity = 0;
                break;
                
            case "horizontal":
                horizontalVelocity = 0;
                break;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

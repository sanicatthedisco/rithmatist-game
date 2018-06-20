package rithmatist;

import java.util.ArrayList;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;

public class GameObject {
	private float x, y;
	
	public static ArrayList<GameObject> allObjects, toAdd, toRemove;
	public static float chalkwidth = 5;

	public static ArrayList<Float> mouseXPositions = new ArrayList<Float>();
	public static ArrayList<Float> mouseYPositions = new ArrayList<Float>();
	
	// Basic constructor
	public GameObject(float x, float y) {
		this.x = x;
		this.y = y;
	}
	
	// Creates array lists for game objects so main can render and update them
	public static void initGameObjects() throws SlickException {
		allObjects = new ArrayList<GameObject>();
		toAdd = new ArrayList<GameObject>();
		toRemove = new ArrayList<GameObject>();
		
		WardLine.drawWardLine();
		
		//allObjects.add(new WardLine(200, 200, 100, 1));
	}
	
	public void update(GameContainer gc, int dt) {};
	
	public void render(GameContainer gc, Graphics g) {};
	
	
	// Getters and setters
	public float getX() {
		return this.x;
	}
	public float getY() {
		return this.y;
	}
	public void setX(float x) {
		this.x = x;
	}
	public void setY(float y) {
		this.y = y;
	}
	public void setLocation(float x, float y) {
		this.x = x;
		this.y = y;
	}
}
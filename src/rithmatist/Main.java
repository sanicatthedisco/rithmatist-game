package rithmatist;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;

public class Main extends BasicGame {
	
	public static Input input;
	
	
	public static final int WIDTH = 1920, HEIGHT = 1080;
	float x = 0;
	float y = 0;
	float speed = .5f;
	
	public Main(String gamename) {
		super(gamename);
	}
	
	@Override
	public void init(GameContainer gc) throws SlickException {
		GameObject.initGameObjects();
		
	}
	
	@Override
	public void update(GameContainer gc, int dt) throws SlickException {
		input = gc.getInput();
		
		/* Test code
		x += dt * speed;
		y += dt * speed;
		*/
		
		WardLine.updateDrawing(gc, dt);
		
		for (GameObject o : GameObject.allObjects) {
			o.update(gc, dt);
		}
		
		for (GameObject o : GameObject.toAdd) {
			GameObject.allObjects.add(o);
		}
		GameObject.toAdd.clear();
		
		for (GameObject o : GameObject.toRemove) {
			GameObject.toRemove.remove(o);
		}
		GameObject.toRemove.clear();
	}

	@Override
	public void render(GameContainer gc, Graphics g) throws SlickException {
		/* Test code
		g.setColor(Color.white);
		g.drawRect(x, y, 100, 100);
		*/
		for (GameObject o : GameObject.allObjects) {
			o.render(gc, g);
		}
		
		WardLine.renderDrawing(gc, g);
	}
	
	public static void main(String[] args) {
		try {
			// Setting up game container
			AppGameContainer appgc;
			appgc = new AppGameContainer(new Main("Test"));
			appgc.setDisplayMode(WIDTH, HEIGHT, false);
			appgc.setShowFPS(false);
			appgc.start();
			
		} catch (SlickException ex) {
			Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
	
	
	// Misc arraylist methods
	public static float getDistance(float x1, float y1, float x2, float y2) {
		return (float) Math.sqrt((Math.pow((x2 - x1), 2) + Math.pow((y2 - y1), 2)));
	}
	
	public static float sigmoid(float x, int iters) {
		float y = (float) ((float) 1 / (1 + Math.pow(Math.E, -x)));
		if (iters > 0) {
			return x;
		} else {
			return sigmoid(y, iters - 1);
		}
	}
	
	public static float getSum(ArrayList<Float> al) {
		float sum = 0;
		for (int i = 0; i < al.size(); i ++) {
			sum += al.get(i);
		}
		return sum;
	}
		
}
		
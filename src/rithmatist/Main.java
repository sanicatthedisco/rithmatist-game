package rithmatist;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;

public class Main extends BasicGame {
	
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
		/* Test code
		x += dt * speed;
		y += dt * speed;
		*/
		
		for (GameObject o : GameObject.allObjects) {
			o.update(gc, dt);
		}
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
		
}
		
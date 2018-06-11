package rithmatist;

import java.util.logging.Level;
import java.util.logging.Logger;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.ScalableGame;
import org.newdawn.slick.SlickException;

public class Main extends BasicGame {
	
	public static final int WIDTH = 1920, HEIGHT = 1080;
	int x = 0;
	int y = 0;
	
	public Main(String gamename) {
		super(gamename);
	}
	
	@Override
	public void init(GameContainer gc) throws SlickException {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void update(GameContainer gc, int dt) throws SlickException {
		x ++;
		y ++;
	}

	@Override
	public void render(GameContainer gc, Graphics g) throws SlickException {
		g.setColor(Color.white);
		g.drawRect(x, y, 100, 100);
	}
	
	public static void main(String[] args) {
		try {
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
		
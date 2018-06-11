package rithmatist;

import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;

public class WardLine extends GameObject {
	/* Line of Warding
	 * A Line of Warding is a circle or ellipse that surrounds the player
	 * They cannot move out of it, it acts as their "home base"
	 * It has 2, 4, 6, or 9 nodes on it
	 * If it is breached, the player loses
	 */
	
	private float radius;
	

	public WardLine(float x, float y, float r) {
		super(x, y);
		this.radius = r;
	}
	
	public void render(GameContainer gc, Graphics g) {
		g.setLineWidth(GameObject.chalkwidth);
		g.drawArc(getX(), getY(), this.radius*2, this.radius*2, 0, 360);
	}

}

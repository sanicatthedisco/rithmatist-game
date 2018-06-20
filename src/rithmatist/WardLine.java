package rithmatist;

import java.util.ArrayList;

import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;

public class WardLine extends GameObject {
	/* Line of Warding
	 * A Line of Warding is a circle or ellipse that surrounds the player
	 * They cannot move out of it, it acts as their "home base"
	 * It has 2, 4, 6, or 9 nodes on it
	 * If it is breached, the player loses
	 */
	
	float radius, strength;
	Color color;
	
	public static boolean beingDrawn = false;
	static boolean mouseDown = false;
	
	static float endDistanceThreshold = 50; // How far apart the end points can be when drawing a ward line
	

	public WardLine(float x, float y, float r, float strength) {
		super(x, y);
		this.radius = r;
		this.strength = (float) Math.pow(1- Math.pow(strength, 2), 2);
		System.out.println(this.strength);
		this.color = new Color(this.strength, this.strength, this.strength);
	}
	
	public static void updateDrawing(GameContainer gc, int dt) {
		if (WardLine.beingDrawn) {
			// Once it's stopped being drawn
			if (!Main.input.isMouseButtonDown(Input.MOUSE_LEFT_BUTTON) && mouseDown) {
				WardLine.beingDrawn = false;
				toAdd.add(WardLine.createWardLine(mouseXPositions, mouseYPositions));
				WardLine.drawWardLine();
			}
			
			if (Main.input.isMouseButtonDown(Input.MOUSE_LEFT_BUTTON)) {
				mouseDown = true;
				GameObject.mouseXPositions.add((float) Main.input.getAbsoluteMouseX());
				GameObject.mouseYPositions.add((float) Main.input.getAbsoluteMouseY());
			} else {
				mouseDown = false;
			}
			
		}
	}
	
	public static void renderDrawing(GameContainer gc, Graphics g) {
		if (WardLine.beingDrawn) {
			for (int i = 0; i < mouseXPositions.size(); i ++) {
				g.fillRect(mouseXPositions.get(i), mouseYPositions.get(i), 3, 3);
			}
			//Gives guide box for center
			//g.fillRect(Main.getSum(mouseXPositions)/mouseXPositions.size(), Main.getSum(mouseYPositions)/mouseXPositions.size(), 10, 10);
		}
	}
	
	public void update(GameContainer gc, int dt) {
	}
	
	public void render(GameContainer gc, Graphics g) {
		g.setLineWidth(GameObject.chalkwidth);
		g.setColor(this.color);
		g.drawArc(getX() - this.radius, getY() - this.radius, this.radius*2, this.radius*2, 0, 360);
		g.drawString(String.valueOf(this.strength), getX(), getY());
	}
	
	public static void drawWardLine() {
		WardLine.beingDrawn = true;
		mouseXPositions.clear();
		mouseYPositions.clear();
	}
	
	public static WardLine createWardLine(ArrayList<Float> xPoints, ArrayList<Float> yPoints) {
		// Find center and distance and evaluate circle, return strength of ward line
		// Find center as centroid of points
		float cX = Main.getSum(xPoints) / xPoints.size();
		float cY = Main.getSum(yPoints) / yPoints.size();
		
		// Strength should be based on the maximum and mininum radii of the shape that was drawn.
		float avgDist = 0;
		float minRadius = Float.MAX_VALUE;
		float maxRadius = 0;
		float tempDist;
		for (int i = 0; i < xPoints.size(); i ++) {
			tempDist = Main.getDistance(xPoints.get(i), yPoints.get(i), cX, cY);
			avgDist += tempDist;
			if (tempDist < minRadius) minRadius = tempDist;
			if (tempDist > maxRadius) maxRadius = tempDist;
		}
		avgDist = avgDist / xPoints.size();
		float strength = (maxRadius - minRadius) / maxRadius; // Ratio keeps it uniform over all size circles
		
		/* Standard deviation method didn't work too well, but here it is
		float stdev = 0;
		for (int i = 0; i < xPoints.size(); i ++) {
			stdev += Math.pow(Main.getDistance(xPoints.get(i), yPoints.get(i), cX, cY) - avgDist, 2);
		}
		stdev = (float) Math.sqrt(stdev/xPoints.size()); //this might need to be a ratio so its fair to circles of all sizes but idk
		*/
		
		// Get distance between first and last point to make sure its a circle
		if (Main.getDistance(xPoints.get(0), yPoints.get(0), xPoints.get(xPoints.size()-1), yPoints.get(yPoints.size()-1)) > endDistanceThreshold) {
			return new WardLine(cX, cY, avgDist, 1); // Strength of 1 should delete circle immediately
		} else {
			//return new WardLine(cX, cY, avgDist, stdev); // For standard deviation method
			return new WardLine(cX, cY, avgDist, strength); // For min/max circle method
		}
		
		
	}

}

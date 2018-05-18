# Generating Rays

## Raycasting Algorithm

	for each pixel in pixels:
		let V be the view ray, V 
		let O be the closest object intersecting with V
		let P be the point where V intersects with O
		let N be the objects normal at P
		let L be the position of the light source
		set pixel to compute_color(P, L, N)

## Camera

The basic components of a camera are the eye, and camera frame. The camera itself is represented as a point in 3D space, called the eye. Each ray must be generated from the camera's orthonormal coordinate frame. This camera frame is a set of orthonormal vectors, u,v,w that describe the orientation of the camera. In order to construct this camera frame, we must provide an up vector, a direction vector, and an eye vector.
(Let x be the cross product operator)

	w = a/|a| 
	u = up x w / | up x w |  
	v = w x u
	
Notice that w and u are normalized. So u,v,w describe the orthornormal coordinate frame for the eye vector, and this is our camera.   


## Viewport 

We will define our viewport as a rectangle with coordinates right,left,top,bottom (r,l,t,b). This rectangle will represent our image, and exist in 3D space as a plane a set number of units from the eye.
To fit an W x H image into a rectangle of size (r − l) x (t − b), the pixels are
spaced a distance (r − l)/W apart horizontally and (t − b)/H apart vertically.
Because the image pixels are positioned by the top left most value offset each pixel by 0.5 to get the centermost point on the pixel.  
This means that the pixel at position (i, j) has the position 

	u = l + (r − l)(i + 0.5)/W ,
	v = b + (t − b)(j + 0.5)/H ,

The viewing plane is the viewport translated into the 3D world space. It is from this virtual viewport that we use construct rays from the eye through each pixel.  
Notice that a ray can be described by the set of points from an origin in a given direction, so
each point along a ray can be denoted by the parametric equation p(t)=o+td, where o and d are the origin and direction vectors, respectively. We define t to be a parameter that will specify the distance from origin. By letting t be some real number, p(t) results in a single point along the ray. 
In our ray eqution we define the origin to be the eye, e and the direction to be the direction from e to a point s=(u,v) on the image plane. 
Since we need a ray from e to s, this can be defined as the following

	p(t) = e + t(s − e).


## Projection
For this example, the viewing direction of the camera will be in the opposite direction of th camera frames w vector.
Given d is the distance from the eye to the viewing plane. 

#### Orthographic Projection

	compute viewport.uv() as (u,v)
	ray.direction = −cam.w
	ray.origin = e + u cam.u + v cam.v


#### Perspective Projection 

	compute viewport.uv() as (u,v)
	ray.direction = −d cam.w + u cam.u + v cam.v
	ray.origin = e
Where d is the distance from the camera to the viewing plane.

# Intersection
At this point we have succesfully calculated the camera rays. From here on we will be calculating whether or not a given ray intersects with a surface, and if so where.


## Surfaces 
Can be defined as geometry primitives, such as spheres, triangles, planes or boxes. However, we can also calculate the point in which a ray intersects with implicitly defined surfaces. An implicity defined surface is defined as an equation f(x,y,z), an a point p is on the sufrace if f(p.x,p.y,p.z)=0

### Normals

## Sphere 
## Plane
## Triangle


# Shading

## Lights
## Flat
## Blinn-Phong 


## Usage
Straighforward psuedocode outlining the usage of each componenet described above

	camera(	{0, 0, 0},	//eye pos
			{0, 0, -1},	//view dir
			{0, 1, 0}));//up
	viewport(400, 300,	// img resolution
			  -1, 1,	//left right
			   1, -1);	//top bottom
	projection(new orthographic_projection());
	shader(new flat_shader());
	raytracer rt(camera, viewport, projection, shader);
	scene scene(BACKGROUND_COLOR)
	hdr_image img;
	rt.render(img, the_scene)


# Credit 
Fundamentals of Computer Graphics 4th Edition, Steve Marschner and Peter Shirley

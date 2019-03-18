#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"
#include <typeinfo>
#include <cstring>

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  image = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  traversals.push_back(&traversal);
  colorPickers.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  unsigned count = 0;

  animation.addFrame(image);
//  count++;
  //make a copy of the image
  //traverse the vector
  for(unsigned i = 0; i < traversals.size(); i++)
  {
    /*if(strncmp(typeid(traversals[i]).name(), "DFS", 3))
      DFS traversal = traversals[i];
    else
      BFS traversal = traversals[i];*/

    //for(it = traversals[i].begin(); it != traversals[i].end(); ++it)
    for(const Point &p : *traversals[i])
    {
      count++;
      image.getPixel(p.x, p.y) = colorPickers[i]->getColor(p.x, p.y);
      if(count % frameInterval == 0)
      {
        animation.addFrame(image);
      //  count++;
      }

    }
  }
  animation.addFrame(image);
//  count++;

  return animation;
}
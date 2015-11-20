/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkPhaseImageToImageFilter_h
#define __itkPhaseImageToImageFilter_h
 
#include "itkImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "vnl/vnl_math.h"
#include "itkWrapPhaseFunctor.h"
 
namespace itk
{
/** \class PhaseImageToImageFilter
 * \brief Base class for filters dealing with phase data.
 *
 * Provides useful methods for dealing with phase, such as pixelwise wrapping and unwrapping.
 *
 */
template< class TInputImage, class TOutputImage >
class PhaseImageToImageFilter:
public ImageToImageFilter< TInputImage, TOutputImage >
{
public:

  // Standard class typedefs.
  typedef PhaseImageToImageFilter                         Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;
  
  // Other typedefs
  typedef Functor::WrapPhaseFunctor< typename TInputImage::PixelType > WrapFunctorType;
 
  // Method for creation through the object factory
  itkNewMacro(Self);
 
  // Run-time type information (and related methods)
  itkTypeMacro(PhaseImageToImageFilter, ImageToImageFilter);

  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:

  PhaseImageToImageFilter(){}
  ~PhaseImageToImageFilter(){}

  /* Wrap the input value within the range -pi to pi.  */
  typename TInputImage::PixelType Wrap( typename TInputImage::PixelType pixel );
                                                        
  /*  Unwrap one pixel value relative to another.  */
  typename TInputImage::PixelType Unwrap( typename TInputImage::PixelType target,
                                          typename TInputImage::PixelType relativeToReference );

//  /* Determine the nearest multiple of two pi that differentiates two inputs.  */
//  typename TInputImage::PixelType TwoPIMultipleDifference( typename TInputImage::PixelType target,
//                                                           typename TInputImage::PixelType relativeToReference );

private:

  PhaseImageToImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
 
};
} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseImageToImageFilter.txx"
#endif

#endif

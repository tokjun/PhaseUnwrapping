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
#ifndef __itkPhaseDerivativeVarianceImageFilter_h
#define __itkPhaseDerivativeVarianceImageFilter_h
 
#include "itkWrappedPhaseDifferencesBaseImageFilter.h"
#include "itkObjectFactory.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"
#include <valarray>
#include "itkCovariantVector.h"
//#include "itkMultiplyImageFilter.h"
//#include "itkRescaleIntensityImageFilter.h"

namespace itk
{
/** \class PhaseDerivativeVarianceImageFilter
 * \brief Calculates locally unwrapped phase derivative variance, an inverse measure of phase quality.
 *
 * This filter assumes a phase image wrapped into the range of -pi to pi as input and
 * provides locally unwrapped phase derivative variance (an inverse measure of phase
 * quality) as output.
 *
 * The class derives from the WrappedPhaseDifferencesBaseImageFilter class,
 * which is an abstract class providing the ComposeVector() method.
 *
 * Briefly, this filter requires two passes.  In the first pass, the the ComposeVector()
 * method is used to create a vector image with as many components as dimensions.  In each
 * dimension, the pixels +/- one index relative to the center are locally unwrapped, and the
 * derivative taken ((right - left)/3).  The derivative calculated in dimension i is saved
 * in component i of the vector image.
 *
 * In the second pass, a neighborhood iterator with radius 1 is used to traverse
 * the vector image.  In each direction, the sum of squared differences from the mean
 * (in that direction) is calculated, followed by the sum of the square roots over the
 * square of the dimension.
 *
 * NOTE: Because this filter is intended to be used as a phase quality guide, the
 * result is inverted and rescaled between 0 and 1, such that higher values represent
 * higher phase quality.  Therefore, the output is linearly related to phase derivative
 * variance, but is not equal to it.  In the future, a method could be added to make
 * this an option.
 *
 */
template< typename TInputImage, typename TOutputImage = TInputImage>
class PhaseDerivativeVarianceImageFilter:
public WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef PhaseDerivativeVarianceImageFilter                                  Self;
  typedef WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                                                Pointer;
  typedef SmartPointer< const Self>                                           ConstPointer;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseDerivativeVarianceImageFilter, WrappedPhaseDifferencesBaseImageFilter);
  
  typedef CovariantVector< double, TInputImage::ImageDimension > TVector;
  typedef Image< TVector, TInputImage::ImageDimension >          TVectorImage;
  
  #ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< TInputImage::ImageDimension, TOutputImage::ImageDimension > ) );
  
  itkConceptMacro( InputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TInputImage::PixelType > ) );
                   
  itkConceptMacro( OutputFloatingPointCheck,
                   ( Concept::IsFloatingPoint< typename TOutputImage::PixelType > ) );
  // End concept checking
  #endif

//  itkSetMacro(Normalize, bool);
//  itkGetConstMacro(Normalize, bool);
//
//  itkSetMacro(Threshold, bool);
//  itkGetConstMacro(Threshold, bool);
//
//  itkSetMacro(ThresholdValue, double );
//  itkGetConstMacro(ThresholdValue, double );
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:

  PhaseDerivativeVarianceImageFilter();
  ~PhaseDerivativeVarianceImageFilter(){}
  
  typedef ConstNeighborhoodIterator< TVectorImage >                NVItType;
  typedef ImageRegionIterator< TInputImage >                       ItType;
//  typedef MultiplyImageFilter< TInputImage, TInputImage >          MultiplyType;
//  typedef RescaleIntensityImageFilter< TInputImage, TOutputImage > RescaleType;
  virtual void GenerateData();
 
private:

  PhaseDerivativeVarianceImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented

//  typename MultiplyType::Pointer m_Negative;
//  typename RescaleType::Pointer m_Rescale;
//  bool m_Normalize;
//  bool m_Threshold;
//  bool m_ThresholdValue;

};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseDerivativeVarianceImageFilter.txx"
#endif
 
#endif

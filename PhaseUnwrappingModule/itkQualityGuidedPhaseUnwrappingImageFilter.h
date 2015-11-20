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
#ifndef __itkQualityGuidedPhaseUnwrappingImageFilter_h
#define __itkQualityGuidedPhaseUnwrappingImageFilter_h

/** ITK headers */
#include "itkPhaseImageToImageFilter.h"
#include "itkObjectFactory.h"
#include "itkImageAlgorithm.h"
#include "itkProgressReporter.h"
#include "itkNeighborhoodIterator.h"

/** Standard and VNL headers */
#include <set>
#include <vector>
#include "vnl/vnl_math.h"

/** Custom headers */
#include "itkPhaseQualityImageFilter.h"
#include "itkIndexValuePair.h"

namespace itk {

/** \class QualityGuidedPhaseUnwrappingImageFilter
 * \brief Uses a quality-guided phase unwrapping algorithm to unwrap wrapped phase images.
 *
 * This filter assumes a phase image wrapped into the range of -pi to pi as input and
 * provides phase quality and unwrapped phase as output.  Phase quality may be retrieved
 * through the GetQuality() method, and unwrapped phase may be retrieved through the
 * GetPhase() method.  The filter requires that the index of a pixel with "true" phase
 * be provided through the SetTruePhase( TImage::IndexType index ) method.
 *
 * Phase quality is calculated by calling the \code{PhaseQualityImageFilter} class.
 * Appropriate methods are provided to interface with this class.
 *
 * The index specified by SetTruePhase is assumed to be unwrapped.  The adjoining pixels
 * (those which are plus/minus one index in each dimension) are then defined to be
 * "candidate" pixels (that is, they are candidates to be the next pixel unwrapped).
 * The candidate pixel with the highest phase quality is unwrapped, and any pixels
 * adjoining it that are not already candidates are defined to be candidate pixels.
 * This process is repeated until all pixels in the image have been unwrapped.
 *
 * This filter has been tested in 2- and 3-dimensional images, but was designed for
 * n-dimensional use.  The algorithm is an adaptation of that provided in
 * "2D Phase Unwrapping: Theory, Algorithms, and Software" by Dennis C Ghiglia and
 * Mark D. Pritt.
 *
 */

template< typename TInputImage, typename TOutputImage = TInputImage >
class QualityGuidedPhaseUnwrappingImageFilter:
public PhaseImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef QualityGuidedPhaseUnwrappingImageFilter              Self;
  typedef PhaseImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                 	               Pointer;
  typedef SmartPointer< const Self >           	               ConstPointer;
  
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

  /** Other types. */
  typedef typename TInputImage::IndexType            IndexType;
  typedef typename TInputImage::PixelType            PixelType;
  typedef Image< bool, TInputImage::ImageDimension > TBinaryImage;
  typedef NeighborhoodIterator< TInputImage >        WorkNItType;
  typedef NeighborhoodIterator< TBinaryImage >       BinaryNItType;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(QualityGuidedPhaseUnwrappingImageFilter, PhaseImageToImageFilter);

  /**
   * Set the index of a pixel with high phase quality.
   * This will be the starting-point of the algorithm.
   */
  itkSetMacro( TruePhase, IndexType );
  itkGetConstMacro( TruePhase, IndexType );

  /** Use this to retrieve the unwrapped phase. */
  TOutputImage* GetPhase();
	
  /** Use this to retrieve the phase quality map. */
  TOutputImage* GetQuality();
  
  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:
	
  QualityGuidedPhaseUnwrappingImageFilter();
  ~QualityGuidedPhaseUnwrappingImageFilter(){}
	
  /** Does the real work. */
  void GenerateData();
	
  /** Declare component filter types */
  typedef PhaseQualityImageFilter< TInputImage > QualityType;
	
  /** Declare set/get variables */
  IndexType m_TruePhase;
	
  /** Used to create the output images when the GetOutput(n) method is called. */
  DataObject::Pointer MakeOutput(unsigned int idx);
 
private:

  QualityGuidedPhaseUnwrappingImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
  
  /** Instantiate component filters */
  typename QualityType::Pointer m_Quality;
 
};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkQualityGuidedPhaseUnwrappingImageFilter.txx"
#endif
 
#endif

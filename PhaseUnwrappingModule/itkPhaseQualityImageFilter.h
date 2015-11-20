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
#ifndef __itkPhaseQualityImageFilter_h
#define __itkPhaseQualityImageFilter_h
 
#include "itkObjectFactory.h"
#include "itkMultiplyImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkPhaseDerivativeVarianceImageFilter.h"

namespace itk
{
/** \class PhaseQualityImageFilter
 * \brief This class handels rescaling and thresholding of a variety of phase quality metrics.
 *
 * Many metrics for phase quality have been proposed, such as phase derivative variance,
 * maximum phase derivative, and pseudocorrelation.  Strictly speaking, pseudocorrelation is
 * measures high quality (higher values indicate higher quality phase) whereas phase derivative
 * variance and maximum phase derivative measure low quality (lower values indicate lower
 * quality).
 *
 * This class provides a common interface to calculate a variety of phase quality metrics.
 * Measures of low quality are negated so that high values indicate high quality.  Moreover,
 * the output is rescaled between 0 and 1.  Optionally, a threshold may be provided so as to
 * yield a binary output.
 *
 */
template< typename TInputImage, typename TOutputImage = TInputImage>
class PhaseQualityImageFilter:
public ImageToImageFilter< TInputImage, TOutputImage >
{
public:

  /** Standard class typedefs. */
  typedef PhaseQualityImageFilter                         Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self>                       ConstPointer;

  typedef enum {PhaseDerivativeVariance=0} QualityType;
 
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(PhaseQualityImageFilter, ImageToImageFilter);
  
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

  itkSetMacro(Threshold, bool);
  itkGetConstMacro(Threshold, bool);

  itkSetMacro(ThresholdValue, double );
  itkGetConstMacro(ThresholdValue, double );
  
  itkSetMacro(QualityMetric, QualityType);
  itkGetConstMacro(QualityMetric, QualityType);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;
 
protected:

  PhaseQualityImageFilter();
  ~PhaseQualityImageFilter(){}
  
  typedef MultiplyImageFilter< TInputImage, TInputImage >                MultiplyType;
  typedef RescaleIntensityImageFilter< TInputImage, TOutputImage >       RescaleType;
  typedef BinaryThresholdImageFilter< TOutputImage, TOutputImage >       ThresholdType;
  typedef PhaseDerivativeVarianceImageFilter< TInputImage, TInputImage > PDVType;
  virtual void GenerateData();
 
private:

  PhaseQualityImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
  
  typename PDVType::Pointer       m_PDVFilter;
  typename MultiplyType::Pointer  m_NegativeFilter;
  typename RescaleType::Pointer   m_RescaleFilter;
  typename ThresholdType::Pointer m_ThresholdFilter;
  bool                            m_Threshold;
  double                          m_ThresholdValue;
  QualityType                     m_QualityMetric;

};

} //namespace ITK

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPhaseQualityImageFilter.txx"
#endif
 
#endif

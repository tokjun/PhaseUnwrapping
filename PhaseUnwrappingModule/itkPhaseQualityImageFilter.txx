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
#ifndef __itkPhaseQualityImageFilter_txx
#define __itkPhaseQualityImageFilter_txx
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
PhaseQualityImageFilter< TInputImage, TOutputImage >
::PhaseQualityImageFilter()
{

  m_QualityMetric = PhaseDerivativeVariance;
  m_Threshold = false;
  m_ThresholdValue = 0.75;

}

template< typename TInputImage, typename TOutputImage >
void
PhaseQualityImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
 
  m_PDVFilter = PDVType::New();
  m_PDVFilter->SetInput( this->GetInput() );

  m_NegativeFilter = MultiplyType::New();
  m_NegativeFilter->SetInput( m_PDVFilter->GetOutput() );
  m_NegativeFilter->SetConstant( -1 );
  
  m_RescaleFilter = RescaleType::New();
  m_RescaleFilter->SetInput( m_NegativeFilter->GetOutput() );
  m_RescaleFilter->SetOutputMaximum( 1 );
  m_RescaleFilter->SetOutputMinimum( 0 );

  if (m_Threshold) {

    m_ThresholdFilter = ThresholdType::New();
    m_ThresholdFilter->SetInput( m_RescaleFilter->GetOutput() );
    m_ThresholdFilter->SetOutsideValue( 0 );
    m_ThresholdFilter->SetInsideValue( 1 );
    m_ThresholdFilter->SetLowerThreshold( m_ThresholdValue );
    m_ThresholdFilter->SetUpperThreshold( 1.1 );

    m_ThresholdFilter->GraftOutput( this->GetOutput() );
    this->GraftOutput( m_ThresholdFilter->GetOutput() );
    this->AllocateOutputs();
    m_ThresholdFilter->Update(); 

  } else {

    m_RescaleFilter->GraftOutput( this->GetOutput() );
    this->GraftOutput( m_RescaleFilter->GetOutput() );
    this->AllocateOutputs();
    m_RescaleFilter->Update();
  
  }
}

template < typename TInputImage, typename TOutputImage > 
void 
PhaseQualityImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 

  os << indent << "Quality Metric: " << m_QualityMetric << std::endl;
  os << indent << "Threshold: " << m_Threshold << std::endl;
  os << indent << "Threshold Value: " << m_ThresholdValue << std::endl;
  
}
 
}// end namespace itk
 
#endif

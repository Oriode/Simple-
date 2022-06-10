#pragma once

#include "../Interval.h"
#include "Neuron.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		class NeuralLayer {
		public:
			NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const ActivationFunc& activationFunc = ActivationFunc());

			constexpr Size getNbFeatures() const;
			constexpr Size getNbNeurons() const;
			constexpr Size getNbParams() const;

			const Size getNbData() const;

			void setNbData(const Size nbData);

			const StaticTable<T, NbFeatures>& getIns(const Size dataI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neuronI) const;
			StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neuronI);
			const StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI) const;
			StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI);
			const StaticTable<T, NbNeurons>& getOuts(const Size dataI) const;
			StaticTable<T, NbNeurons>& getOuts(const Size dataI);
			const StaticTable<T, NbNeurons>& getDeltas(const Size dataI) const;
			StaticTable<T, NbNeurons>& getDeltas(const Size dataI);

			const Vector< StaticTable<T, NbFeatures>>& getInVector() const;
			const Vector< StaticTable<T, NbNeurons>>& getOutVector() const;
			Vector< StaticTable<T, NbNeurons>>& getOutVector();
			const Vector<StaticTable<T, NbNeurons>>& getDeltaVector() const;
			Vector<StaticTable<T, NbNeurons>>& getDeltaVector();

			const ActivationFunc& getActivationFunc() const;

			T computeY(const Size neuronI, const Size dataI) const;
			T computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable) const;

			const T& getOut(const Size neuronI, const Size dataI) const;
			const T& getParam(const Size neuronI, const Size paramI) const;
			const T& getGrad(const Size neuronI, const Size paramI) const;

			void setGrad(const Size neuronI, const Size paramI, const T& v);
			void setParam(const Size neuronI, const Size paramI, const T& v);
			void setOut(const Size neuronI, const Size dataI, const T& v);

			const Neuron<T, NbFeatures, ActivationFunc>& getNeuron(const Size neuronI) const;
			Neuron<T, NbFeatures, ActivationFunc>& getNeuron(const Size neuronI);

			const Mat<T>& getParamMat() const;
			Mat<T>& getParamMat();

			const StaticTable<T, NbNeurons>& computeForwardPropagation(const Size dataI);
			void computeForwardPropagation(const StaticTable<T, NbFeatures> & featureTable, StaticTable<T, NbNeurons> & outTable) const;
			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);

			void computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector);
			template<Size NbFeaturesNext, Size NbNeuronsNext>
			void computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, ActivationFunc>& nextNeuralLayer);

			void updateModel(const T& learningRate = T(0.01));

			T computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;

		private:
			const Vector<StaticTable<T, NbFeatures>>* inTableVector;		// Matrix of input of size [NbData, NbFeatures]
			Vector<StaticTable<T, NbNeurons>> outTableVector;				// Matrix of output of size [NbData, NbNeurons]
			Vector<StaticTable<T, NbNeurons>> deltaTableVector;				// Matrix of deltas of size [NbData, NbFeatures]

			Mat<T> paramMat;	// Matrix of params of size [NbNeurons, NbFeatures + 1]
			Mat<T> gradMat;		// Matrix of params of size [NbNeurons, NbFeatures + 1]

			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& paramTableTable;		// Reference to paramMat
			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& gradTableTable;		// Reference to gradMat

			// StaticTable<Neuron<T, NbFeatures, ActivationFunc>, NbNeurons> neuronTable;

			const ActivationFunc activationFunc;		// Activation func
		};

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const ActivationFunc& activationFunc) :
			inTableVector(inTableVector),
			paramMat(NbNeurons, NbFeatures + Size(1)),
			gradMat(NbNeurons, NbFeatures + Size(1)),
			paramTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( paramMat.getData() )),
			gradTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( gradMat.getData() )),
			activationFunc(activationFunc) {
			/*for ( Size neuronI(0); neuronI < this->paramMat.getSize(); neuronI++ ) {
				StaticTable<T, NbFeatures + Size(1)> paramTable(getParams(neuronI));
				for ( Size paramI(0); paramI < paramTable.getSize(); paramI++ ) {
					paramTable[ paramI ] = Math::randomF();
				}
			}*/
			paramMat.randomF();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNbNeurons() const {
			return NbNeurons;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Size NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNbData() const {
			return this->outTableVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::setNbData(const Size nbData) {
			this->outTableVector.resize(nbData);
			this->deltaTableVector.resize(nbData);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getIns(const Size dataI) const {
			return this->inTableVector->getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getParams(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc> * >( this )->getParams(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getParams(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->paramMat.getDataM(neuronI));
			return this->paramTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getGrads(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc> * >( this )->getGrads(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getGrads(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->gradMat.getDataM(neuronI));
			return this->gradTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getOuts(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc> * >( this )->getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getOuts(const Size dataI) {
			return this->outTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getDeltas(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc> * >( this )->getDeltas(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getDeltas(const Size dataI) {
			return this->deltaTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Vector<StaticTable<T, NbFeatures>>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getInVector() const {
			return *this->inTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getOutVector() const {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getOutVector() {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getDeltaVector() const {
			return this->deltaTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getDeltaVector() {
			return this->deltaTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const ActivationFunc& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getActivationFunc() const {
			return this->activationFunc;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeY(const Size neuronI, const Size dataI) const {
			return computeY(neuronI, getIns(dataI));
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable) const {
			return Neuron<T, NbFeatures, ActivationFunc>::computeY(featureTable, getParams(neuronI), this->activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::setOut(const Size neuronI, const Size dataI, const T& v) {
			this->outTableVector.getValueI(dataI)[ neuronI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getOut(const Size neuronI, const Size dataI) const {
			return this->outTableVector.getValueI(dataI)[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getParam(const Size neuronI, const Size paramI) const {
			return getParams(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::setParam(const Size neuronI, const Size paramI, const T& v) {
			getParams(neuronI)[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getGrad(const Size neuronI, const Size paramI) const {
			return getGrads(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::setGrad(const Size neuronI, const Size paramI, const T& v) {
			getGrads(neuronI)[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNeuron(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc> * >( this )->getNeuron(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getNeuron(const Size neuronI) {
			return this->neuronTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getParamMat() const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>* >( this )->getParamMat();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::getParamMat() {
			return this->paramMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeForwardPropagation(const Size dataI) {
			computeForwardPropagation(getIns(dataI), getOuts(dataI));

			return getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeForwardPropagation(const StaticTable<T, NbFeatures>& featureTable, StaticTable<T, NbNeurons>& outTable) const {
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				const T y(computeY(neuronI, featureTable));
				outTable[ neuronI ] = y;
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			const T sizeInverse(T(1) / T(getNbData()));

			for ( Size paramI(0); paramI < getNbFeatures(); paramI++ ) {
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

					T dotSum(0);
					for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
						dotSum += getIns(dataI)[ paramI ] * getDeltas(dataI)[ neuronI ];
					}

					dotSum *= sizeInverse;
					setGrad(neuronI, paramI, dotSum);
				}
			}
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

				T dotSum(0);
				for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
					dotSum += getDeltas(dataI)[ neuronI ];
				}

				dotSum *= sizeInverse;
				setGrad(neuronI, getNbFeatures(), dotSum);
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				StaticTable<T, NbNeurons>& deltaVecTable(getDeltas(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					deltaVecTable[ neuronI ] = outTable[ neuronI ] - expectedYTable[ neuronI ];
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::updateModel(const T& learningRate) {
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				for ( Size paramI(0); paramI < getNbParams(); paramI++ ) {
					const T& grad(getGrads(neuronI)[ paramI ]);
					T& param(getParams(neuronI)[ paramI ]);
					param = param - learningRate * grad;
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T& expectedY(expectedYTable[ neuronI ]);
					const T& y(outTable[ neuronI ]);
					costSum += expectedY * Math::log(y) + ( T(1) - expectedY ) * Math::log(T(1) - y);
				}
			}

			return -costSum / T(getNbData());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T delta(expectedYTable[ neuronI ] - outTable[ neuronI ]);
					costSum += delta * delta;
				}
			}

			return costSum / T(getNbData() * Size(2));
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			StaticTable<T, NbNeurons> meanVec;
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] = T(0);
			}
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& expectedTable(expectedOutTableVector.getValueI(dataI));

				for ( Size neuronI(0); neuronI < meanVec.getSize(); neuronI++ ) {
					meanVec[ neuronI ] += expectedTable[ neuronI ];
				}
			}
			const T sizeInverse(T(1) / T(getNbData()));
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] *= sizeInverse;
			}

			T errSum(0);
			T meanSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& expectedTable(expectedOutTableVector.getValueI(dataI));
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));

				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T y(outTable[ neuronI ]);
					const T expectedY(expectedTable[ neuronI ]);
					const T err(expectedY - y);
					const T mean(expectedY - meanVec[ neuronI ]);

					errSum += err * err;
					meanSum += mean * mean;
				}
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename ActivationFunc>
		template<Size NbFeaturesNext, Size NbNeuronsNext>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, ActivationFunc>::computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, ActivationFunc>& nextNeuralLayer) {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeuronsNext>& nextDeltaVecTable(nextNeuralLayer.getDeltas(dataI));
				StaticTable<T, NbNeurons>& deltaVecTable(getDeltas(dataI));

				for ( Size neuronI(0); neuronI < deltaVecTable.getSize(); neuronI++ ) {
					const ActivationFunc& activationFunc(getActivationFunc());

					T dotSum(0);
					for ( Size nextNeuronI(0); nextNeuronI < nextDeltaVecTable.getSize(); nextNeuronI++ ) {
						const StaticTable<T, NbFeaturesNext + Size(1)>& paramTable(nextNeuralLayer.getParams(nextNeuronI));
						dotSum += paramTable[ neuronI ] * nextDeltaVecTable[ nextNeuronI ];
					}
					deltaVecTable[ neuronI ] = activationFunc.grad(dotSum, outTable[ neuronI ]);
				}
			}
		}

	}

}
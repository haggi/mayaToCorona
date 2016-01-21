#ifndef CORONA_MAP_H
#define CORONA_MAP_H

#include <maya/MRenderUtil.h>
#include <maya/MMatrix.h>
#include <maya/MFloatMatrix.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MPointArray.h>
#include <maya/MFloatPointArray.h>
#include <maya/MGlobal.h>
#include <maya/MColor.h>
#include "utilities/logging.h"
#include "CoronaUtils.h"
#include "CoronaCore/api/Api.h"

bool textureFileSupported(MString fileName);

class SidedMap : public Corona::Abstract::Map {
public:
    virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
		if (context.isBacksideHit()) {
            return Corona::Rgb::RED * 100;
        } else {
            return Corona::Rgb::BLUE * 100;
        }
    }

    virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
        return evalColor(context, cache, outAlpha).grayValue();
    }

    virtual Corona::Dir evalBump(const Corona::IShadeContext&, Corona::TextureCache*) {
        STOP; //currently not supported
    }

    virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
        STOP; //currently not supported
    }
	virtual void getChildren(Corona::Stack<Corona::Resource*>&) {}
};

static int c = 0;


class mtco_MapLoader : public Corona::Object {
public:
	MColor colorGain;
	MColor colorOffset;
	float exposure;
	Corona::TextureShader::Config tsConfig;
	MString fileName;

	mtco_MapLoader::mtco_MapLoader(MObject& mobject);
	mtco_MapLoader::~mtco_MapLoader();

	Corona::Abstract::Map* loadBitmap(const Corona::String& filename) 
	{
		class TextureMap : public Corona::Abstract::Map {
		protected:
			Corona::TextureShader shader;
		public:
			MColor colorGain;
			MColor colorOffset;
			float exposure;

			TextureMap(const Corona::String& filename, const int mapChannel) {
				Corona::TextureShader::Config config;
				config.mapping.uvwMapChannel = mapChannel;
				config.texture = Corona::TextureShader::getImageTexture(filename);				
				this->shader.configure(config);
			}

			TextureMap(const Corona::String& filename, const int mapChannel, Corona::TextureShader::Config con, MColor gain, MColor offset, float exp) 
			{
				Corona::TextureShader::Config config = con;
				config.mapping.uvwMapChannel = mapChannel;
				config.texture = Corona::TextureShader::getImageTexture(filename);
				if (!config.texture.isValid())
					Logging::error(MString("Could not load texture file: ") + filename + " correctly.");
				this->shader.configure(config);
				colorGain = gain;
				colorOffset = offset;
				exposure = exp;
			}

			virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
				outAlpha = 1.f;
				bool outsideDummy;
				//Corona::Matrix33 bb = context.bumpBase(0);
				//Corona::Dir duvw = context.dUvw(0);
				//Corona::Pos uvw = context.getMapCoords(0);
				//Corona::IPrimitive *ip = context.getPrimitive();
				Corona::Rgb result = shader.eval(context, true, outsideDummy);
				result = result * toCorona(colorGain) + toCorona(colorOffset);
				result *= powf(2.0f, exposure);	
				return result;
				//return shader.eval(context, true, outsideDummy);
			}

			virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
				return evalColor(context, cache, outAlpha).grayValue();
			}

			virtual Corona::Dir evalBump(const Corona::IShadeContext& context, Corona::TextureCache* cache) {
				bool outside;
				return shader.evalBumpMap(context, outside) * toCorona(colorGain).grayValue();
			}

			virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
				//shader.renderTo(output);
			}


			virtual Corona::String name() const {
				return "TextureMap";
			}
			virtual void getChildren(Corona::Stack<Corona::Resource*>&) {}

			virtual bool exportMap(Corona::IResourceManager& resourceManager, Corona::XmlWriterNode& outXml) const { return true; }

		};

		//return new TextureMap(filename, 0);
		return new TextureMap(this->fileName.asChar(), 0, tsConfig, colorGain, colorOffset, exposure);
	}
};

class mtco_FileLoader : public Corona::Object {
public:
	Corona::Abstract::Map* loadBitmap(const Corona::String& filename)
	{
		class TextureMap : public Corona::Abstract::Map {
		protected:
			Corona::TextureShader shader;
		public:
			TextureMap(const Corona::String& filename, const int mapChannel) {
				Corona::TextureShader::Config config;
				config.mapping.uvwMapChannel = mapChannel;
				config.texture = Corona::TextureShader::getImageTexture(filename);

				this->shader.configure(config);
			}

			virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
				outAlpha = 1.f;
				bool outsideDummy;
				return shader.eval(context, true, outsideDummy);
			}

			virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
				outAlpha = 1.f;

				bool outsideDummy;
				return shader.eval(context, true, outsideDummy).grayValue();
			}

			virtual Corona::Dir evalBump(const Corona::IShadeContext& context, Corona::TextureCache* cache) {
				STOP;
			}

			virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
				//shader.renderTo(output);
			}


			virtual Corona::String name() const {
				return "TextureMap";
			}
			virtual void getChildren(Corona::Stack<Corona::Resource*>&) {}

			virtual bool exportMap(Corona::IResourceManager& resourceManager, Corona::XmlWriterNode& outXml) const { return true; }

		};

		return new TextureMap(filename, 0);
	}
};

//class mtco_MapLoader : public Corona::Object {
//public:
//	MColor colorGain;
//	MColor colorOffset;
//	float exposure;
//
//	Corona::Abstract::Map* loadBitmap(const Corona::String& filename) {
//
//		class TextureMap : public Corona::Abstract::Map {
//		protected:
//			Corona::TextureShader shader;
//		public:
//			MColor colorGain;
//			MColor colorOffset;
//			float exposure;
//
//			TextureMap(const Corona::String& filename, const int mapChannel) {
//				Corona::TextureShader::Config config;
//				config.mapping.uvwMapChannel = mapChannel;
//				config.texture = Corona::TextureShader::getImageTexture(filename);
//				this->shader.configure(config);
//			}
//
//			virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//				outAlpha = 1.f;
//				bool outsideDummy;
//				float ex = exposure;
//				Corona::Rgb envColor = shader.eval(context, true, outsideDummy);
//				//if (c < 100)
//				//{
//				//	std::cout << "evalEnvCol " << envColor.r() << " " << envColor.g() << " " << envColor.g() << "\n";
//				//	c++;
//				//}
//				return envColor;
//			}
//
//			/// \brief Same as evalColor, only scalar value is returned
//			virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//				outAlpha = 1.f;
//				bool outsideDummy;
//				return shader.eval(context, true, outsideDummy).grayValue();
//			}
//
//			/// \brief Evaluates bump mapping for this texture and returns a vector that have to be added to the
//			///        current normal to create the bump effect (the normal perturbation)
//			virtual Corona::Dir evalBump(const Corona::IShadeContext& context, Corona::TextureCache* cache) {
//				STOP;
//			}
//
//			/// \brief Renders the map to given output bitmap. Sets the output dimensions to adequate values.
//			virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
//				shader.renderTo(output);
//			}
//
//			virtual Corona::String name() const {
//				return "TextureMap";
//			}
//			virtual void getChildren(Corona::Stack<Corona::Resource*>&) {}
//
//		};
//
//		TextureMap *texMap = new TextureMap(filename, 0);
//		texMap->colorGain = colorGain;
//		texMap->colorOffset = colorOffset;
//		texMap->exposure = exposure;
//		return texMap;
//	}
//};

// Utility class for loading bitmap textures from files. In future, various procedural textures should be also 
// loaded using this class.
//class MapLoader : public Corona::Object {
//public:
//
//	MColor colorGain;
//	MColor colorOffset;
//	float  exposure;
//
//     Corona::Abstract::Map* loadBitmap(const Corona::String& filename) {
//        Corona::Bitmap<Corona::Rgb> data;
//        Corona::loadImage(filename, data);
//		
//        class TextureMap : public Corona::Abstract::Map {
//        protected:
//            Corona::TextureShader shader;
//        public:
//			Corona::Rgb  colorGain;
//			Corona::Rgb  colorOffset;
//			float  exposure;
//			
//            TextureMap(const Corona::Bitmap<Corona::Rgb>& data, const int mapChannel) {
//                shader.data = data;
//                shader.mapChannel = mapChannel;
//            }
//
//            virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//                outAlpha = 1.f;
//				Corona::Rgb result = shader.eval(context, false);
//				result *= this->colorGain;
//				result += this->colorOffset;
//				result *= pow(2, this->exposure);
//				return result;
//            }
//
//            /// \brief Same as evalColor, only scalar value is returned
//            virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//                outAlpha = 1.f;
//                return shader.eval(context, false).grayValue();
//            }
//
//            /// \brief Evaluates bump mapping for this texture and returns a vector that have to be added to the
//            ///        current normal to create the bump effect (the normal perturbation)
//            virtual Corona::Dir evalBump(const Corona::IShadeContext& context, Corona::TextureCache* cache) {
//                STOP;
//            }
//
//            /// \brief Renders the map to given output bitmap. Sets the output dimensions to adequate values.
//            virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
//                shader.renderTo(output);
//            }
//
//            virtual Corona::String name() const {
//                return "TextureMap";
//            }
//			virtual void getChildren(Corona::Stack<Corona::Resource*>&) {}
//        };
//
//		TextureMap *tm = new TextureMap(data, 0);
//		tm->colorGain = Corona::Rgb(this->colorGain.r, this->colorGain.g, this->colorGain.b);
//		tm->colorOffset = Corona::Rgb(this->colorOffset.r, this->colorOffset.g, this->colorOffset.b);
//		tm->exposure = this->exposure;
//		return(tm);
//    }
//};
//
//
//// A sample texture, that just maps the world position to a red-blue grid
//class CheckerMap : public Corona::Abstract::Map {
//public:
//    virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//        //const Corona::Pos pos = context.getPosition()/3;
//		const Corona::Pos pos = context.getMapCoords(0) * 10.0f;
//        const int tmp = int(floor(pos.x()))+int(floor(pos.y()))+int(floor(pos.z()));
//        outAlpha = 1.f;
//        if(tmp%2) {
//            return Corona::Rgb::RED;
//        } else {
//            return Corona::Rgb::BLUE;
//        }
//    }
//
//    virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//        return evalColor(context, cache, outAlpha).grayValue();
//    }
//
//    virtual Corona::Dir evalBump(const Corona::IShadeContext&, Corona::TextureCache*) {
//        STOP; //currently not supported
//    }
//
//    virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
//        STOP; //currently not supported
//    }
//};
//
//// A sample texture, that just maps the world position to a red-blue grid
//class MayaMap : public Corona::Abstract::Map {
//public:
//    MString otherSidePlugName;
//	MayaMap(MString otherSidePlugName){otherSidePlugName = otherSidePlugName;};
//
//	virtual Corona::Rgb evalColor(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) 
//	{
//		Corona::Dir normal = context.getGeometryNormal();
//        const Corona::Pos pos = context.getPosition();
//		const Corona::Pos uvw = context.getMapCoords(0);
//
//		MFloatMatrix camMatrix;
//		camMatrix.setToIdentity();
//		MFloatPointArray pointArray, refPoints;
//		MFloatArray uArray, vArray, filterSizes;
//		MFloatVectorArray normals, uTangents, vTangents, resultColors, resultTransparencies;
//		pointArray.append(pos.x(), pos.y(), pos.z());
//		uArray.append(uvw.x());
//		vArray.append(uvw.y());
//		normals.append(MFloatVector(normal.x(), normal.y(), normal.z()));
//		//MRenderUtil::sampleShadingNetwork(otherSidePlugName, numFollicles, false, true, matrix, nullptr, &uCoords, &vCoords, nullptr, nullptr, nullptr, nullptr, nullptr, resultColors, resultTransparencies);
//
//		//MStatus s = MRenderUtil::sampleShadingNetwork(otherSidePlugName, 1, false, true, camMatrix, &pointArray, &uArray, &vArray, &normals, nullptr, nullptr, nullptr, nullptr, resultColors, resultTransparencies);
//		//if( !s )
//		//	MGlobal::displayInfo(MString("sample problem: ") + s.errorString());
//		//if( resultColors.length() > 0)
//		//{
//		//	MFloatVector c(resultColors[0].x, resultColors[0].y, resultColors[0].z);
//		//	if( s )
//		//		return Corona::Rgb(resultColors[0].x, resultColors[0].y, resultColors[0].z);
//		//	else{
//		//		MGlobal::displayInfo(MString("sample problem: ") + s.errorString());
//		//		return Corona::Rgb(0,0,1);
//		//	}
//		//}else{
//		//	if( !s )
//		//		MGlobal::displayInfo(MString("sample problem: ") + s.errorString());
//		//	return Corona::Rgb(0,0,1);
//		//}
//		outAlpha = 1.0f;
//		return Corona::Rgb(0,0,1);
//    }
//
//    virtual float evalMono(const Corona::IShadeContext& context, Corona::TextureCache* cache, float& outAlpha) {
//        return evalColor(context, cache, outAlpha).grayValue();
//    }
//
//    virtual Corona::Dir evalBump(const Corona::IShadeContext&, Corona::TextureCache*) {
//        STOP; //currently not supported
//    }
//
//    virtual void renderTo(Corona::Bitmap<Corona::Rgb>& output) {
//        STOP; //currently not supported
//    }
//};

#endif

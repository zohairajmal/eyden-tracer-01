#include "ICamera.h"
/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution), m_pos(pos), m_dir(dir), m_up(up)
	{
		m_focus = 1 / tan(angle / 2 * Pi / 180);
		m_yAxis = -m_up;
		m_xAxis = m_dir.cross(m_up);
		m_aspect = (float)resolution.width / (float)resolution.height;
	}
	virtual ~CCameraPerspective(void) = default;
	virtual bool InitRay(float x, float y, Ray &ray) override
	{
		float ndcx = (x + 0.5) / getResolution().width;
		float ndcy = (y + 0.5) / getResolution().height;
		float sscx = (2 * ndcx - 1) * m_aspect;
		float sscy = (2 * ndcy - 1);
		ray.dir = normalize((m_dir * m_focus) + (sscx * m_xAxis) + (sscy * m_yAxis));
		ray.org = m_pos;
		ray.t = std::numeric_limits<float>::max();
		return true;
	}

private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;
	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

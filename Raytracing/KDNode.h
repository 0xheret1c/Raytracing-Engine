#pragma once

class KDNode {
private:

public:
	BoundingBox bbox;
	KDNode* left;
	KDNode* right;
	std::vector<Triangle*> triangles;

	KDNode() {

	}

	static KDNode* build(std::vector<Triangle*>& tris, int depth) {
		KDNode* node = new KDNode();
		node->triangles = tris;
		node->left = NULL;
		node->right = NULL;
		node->bbox = BoundingBox();

		int triCount = tris.size();

		if (tris.size() == 0) {
			return node;
		}

		if (tris.size() == 1) {
			node->bbox = tris[0]->get_bounding_box();
			node->left = new KDNode();
			node->right = new KDNode();
			node->left->triangles = std::vector<Triangle*>();
			node->right->triangles = std::vector<Triangle*>();
			return node;
		}

		node->bbox = tris[0]->get_bounding_box();

		for (int i = 1; i < triCount; i++) {
			node->bbox.expand(tris[i]->get_bounding_box());
		}

		/*Eigen::Vector3d midpt = Eigen::Vector3d(0, 0, 0);
		for (int i = 0; i < triCount; i++) {
			midpt += (tris[i]->get_midpoint() * (1.0 / triCount));
		}*/

		Eigen::Vector3d midpt = node->bbox.midPoint();

		std::vector<Triangle*> left_tris;
		std::vector<Triangle*> right_tris;
		int axis = node->bbox.longest_axis();

		for (int i = 0; i < triCount; i++) {
			switch (axis) {
				case 0:
					midpt.x() >= tris[i]->get_midpoint().x() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
					break;
				case 1:
					midpt.y() >= tris[i]->get_midpoint().y() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
					break;
				case 2:
					midpt.z() >= tris[i]->get_midpoint().z() ? right_tris.push_back(tris[i]) : left_tris.push_back(tris[i]);
					break;
			}
		}

		if (left_tris.size() == 0 && right_tris.size() > 0) {
			left_tris = right_tris;
		}
		if (right_tris.size() == 0 && left_tris.size() > 0) {
			right_tris = left_tris;
		}

		int matches = 0;
		for (int i = 0; i < left_tris.size(); i++) {
			for (int j = 0; j < right_tris.size(); j++) {
				if (left_tris[i] == right_tris[j]) {
					matches++;
				}
			}
		}

		if ((double)matches / left_tris.size() < 0.5 && (double)matches / right_tris.size() < 0.5) {
			node->left = KDNode::build(left_tris, depth + 1);
			node->right = KDNode::build(right_tris, depth + 1);
		}
		else {
			node->left = new KDNode();
			node->right = new KDNode();
			node->left->triangles = std::vector<Triangle*>();
			node->right->triangles = std::vector<Triangle*>();
		}

		return node;
	}

	static bool hit(KDNode* node, Ray& ray, double& t, double &u, double &v, double &umin, double &vmin, double& tmin, RaycastHit *hit) {
		if (node->bbox.intersects(ray)) {
			//std::cout << "HIT BOUNDING BOX" << std::endl;
			bool hit_tri = false;
			
			if (node->left->triangles.size() > 0 || node->right->triangles.size() > 0) {
				/*double tmin1 = tmin;
				double tmin2 = tmin;
				RaycastHit hit1;
				RaycastHit hit2;*/
				bool hitleft = KDNode::hit(node->left, ray, t, u, v, umin, vmin, tmin, hit);
				bool hitright = KDNode::hit(node->right, ray, t, u, v, umin, vmin, tmin, hit);

				//tmin = min(tmin1, tmin2);
				/*if (tmin1 < tmin2) {
					hit = &hit1;
				}
				else {
					hit = &hit2;
				}*/

				return hitleft || hitright;
			}
			else {
				//std::cout << "NO MORE BOXES" << std::endl;
				int triCount = node->triangles.size();
				for (int i = 0; i < triCount; i++) {
					//std::cout << node->triangles[i]->n << std::endl;
					if (node->triangles[i]->rayTriangleIntersect(ray.origin, ray.direction, t, u, v)) {
						if (t <= tmin) {
							hit_tri = true;
							tmin = t;
							hit->point = ray.origin + t * ray.direction;
							hit->n = node->triangles[i]->n;
							umin = u;
							vmin = v;
							hit->uv0 = node->triangles[i]->uv0;
							hit->uv1 = node->triangles[i]->uv1;
							hit->uv2 = node->triangles[i]->uv2;
						}
						//std::cout << "Hit TRIANGLE" << std::endl;
					}
				}
				if (hit_tri) {
					hit->point = ray.origin + tmin * ray.direction;
					return true;
				}
				return false;
			}
		}
		return false;
	}
};
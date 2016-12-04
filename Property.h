#ifndef __PROPERTY_H__
#define __PROPERTY_H__



namespace MyNamespace
{
		//----------------------------------------------------------------------
		// scalar property �� get ���� ����
		//----------------------------------------------------------------------
	template<typename T>
	class get
	{
	private:
			const T& m_data;
	public:
			typedef T volatileType;
			get(const T& data) : m_data(data) { }
			get(const get<T>& get) : m_data(get.m_data) { }
			operator const T&() const
		{
				return m_data;
		}
			const T& operator=(const T& data);
	private:
			get<T>& operator=(const get<T>&);
	};
		//----------------------------------------------------------------------
		// scalar property �� set ���� ����
		//----------------------------------------------------------------------
	template<typename T>
	class set
	{
	private:
			T& m_data;
	public:
			typedef T volatileType;
			set(T& data) : m_data(data) { }
			set(const set<T>& set) : m_data(set.m_data) { }
			const T& operator=(const T& data)
		{
				m_data = data;
				return m_data;
		}
			operator const T&() const;
	private:
			set<T>& operator=(const set<T>&);
	};
		//----------------------------------------------------------------------
		// scalar property �� get/set ���� ����
		//----------------------------------------------------------------------
	template <typename T>
	class all
	{
	private:
			get<T> m_get;
			set<T> m_set;
	public:
			typedef T volatileType;
			all(T& data) : m_get(data), m_set(data) { }
			operator const T&() const
		{
				return (m_get.operator const T&());
		}
			const T& operator=(const T& data)
		{
				return m_set.operator=(data);
		}
	private:
			all<T>& operator=(const all<T>&);
	};
		//----------------------------------------------------------------------
		// propery host class : scalar property ������ ���� ���Ǵ� Ŭ����.
		//
		// - property<int>     : int �� get/set �� property
		// - property<int,get> : int �� get scalar property
		// - property<int,set> : int �� set scalar property
		//----------------------------------------------------------------------
	template <class T, template<class> class PropertyPolicy = all >
	class property : public PropertyPolicy<T>
	{
	public:
			property(T& data) : PropertyPolicy<T>(data) { }
			operator const T&() const
		{
				return PropertyPolicy<T>::operator const T&();
		}
			Const T& operator=(const T& data)
		{
				return PropertyPolicy<T>::operator=(data);
		}
			const T& get() const

		{
				return PropertyPolicy<T>::operator const T&();
		}

			void set(const T& data)
		{
				PropertyPolicy<T>::operator=(data);
		}
	private: // prohibit
			property(const property<T, PropertyPolicy>&);
			property& operator=(const property<T, PropertyPolicy>&);
	}; // class property
} // namespace

#endif // __HELLOWORLD_SCENE_H__

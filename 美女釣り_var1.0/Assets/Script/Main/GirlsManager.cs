using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GirlsManager : MonoBehaviour {

    [SerializeField] GameObject[] m_Girls;
    [SerializeField] byte maxGirl;

	// Use this for initialization
	void Start () {

        float random_X, random_Y;

        random_X = Random.Range(0f, 1f);
        random_Y = Random.Range(0f, 1f);

        var randomForce = new Vector2(random_X, random_Y);

        this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);

        for (int i=0;i<maxGirl;i++)
        {
            var random = 0;
            random = Random.Range(0, m_Girls.Length);

            Instantiate(m_Girls[random]);
        }
	}

    // ランダムな女の子生成
    public void GirlSpawn()
    {
        var random = 0;
        float random_X = Random.Range(0, Screen.width);
        float random_Y = Random.Range(0, Screen.height);

        random = Random.Range(0, m_Girls.Length);

        Instantiate(m_Girls[random], this.gameObject.transform);
    }
}

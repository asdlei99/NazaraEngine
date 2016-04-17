#include <Nazara/Math/Rect.hpp>
#include <Catch/catch.hpp>

SCENARIO("Rect", "[MATH][RECT]")
{
	GIVEN("Two same Nz::Rectangles center and unit lengths")
	{
		Nz::Rectf firstCenterAndUnit(0.f, 0.f, 1.f, 1.f);
		Nz::Rectf secondCenterAndUnit(Nz::Recti(Nz::Vector2i::Unit(), Nz::Vector2i::Zero()));

		WHEN("We ask if they are the same")
		{
			THEN("They should be")
			{
				REQUIRE(firstCenterAndUnit == secondCenterAndUnit);
				REQUIRE(firstCenterAndUnit.GetCenter() == secondCenterAndUnit.GetCenter());
				REQUIRE(firstCenterAndUnit.GetCorner(Nz::RectCorner_LeftBottom) == secondCenterAndUnit.GetCorner(Nz::RectCorner_LeftBottom));
				CHECK(firstCenterAndUnit.IsValid());
			}
		}

		WHEN("We move one from (0.5, 0.5)")
		{
			firstCenterAndUnit.Translate(Nz::Vector2f(0.5f, 0.5f));

			THEN("The collision should be (0.5, 0.5) -> (0.5, 0.5)")
			{
				Nz::Rectf tmp;
				CHECK(firstCenterAndUnit.Intersect(secondCenterAndUnit, &tmp));
				REQUIRE(tmp == Nz::Rectf(0.5f, 0.5f, 0.5f, 0.5f));
			}
		}

		WHEN("We make an empty")
		{
			THEN("It's not valid")
			{
				CHECK(!(firstCenterAndUnit * 0.f).IsValid());
			}
		}

		WHEN("We ask for infos")
		{
			THEN("These results are expected")
			{
				REQUIRE(firstCenterAndUnit.GetLengths() == Nz::Vector2f::Unit());
				REQUIRE(firstCenterAndUnit.GetMaximum() == Nz::Vector2f::Unit());
				REQUIRE(firstCenterAndUnit.GetMinimum() == Nz::Vector2f::Zero());
				REQUIRE(firstCenterAndUnit.GetNegativeVertex(Nz::Vector2f::Unit()) == Nz::Vector2f::Zero());
				REQUIRE(firstCenterAndUnit.GetPosition() == Nz::Vector2f::Zero());
				REQUIRE(firstCenterAndUnit.GetPositiveVertex(Nz::Vector2f::Unit()) == Nz::Vector2f::Unit());

			}
		}

		WHEN("We try to lerp")
		{
			THEN("Compilation should be fine")
			{
				Nz::Rectf nullRect = Nz::Rectf::Zero();
				Nz::Rectf centerAndUnit = firstCenterAndUnit;
				Nz::Rectf result(Nz::Vector2f::Zero(), Nz::Vector2f::Unit() * 0.5f);

				REQUIRE(Nz::Rectf::Lerp(nullRect, centerAndUnit, 0.5f) == result);
			}
		}
	}
}
